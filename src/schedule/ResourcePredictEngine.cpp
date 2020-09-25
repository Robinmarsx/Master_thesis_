// Copyright (C) 2019 Yu Yang
//
// This file is part of Vesyla.
//
// Vesyla is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Vesyla is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Vesyla.  If not, see <http://www.gnu.org/licenses/>.

#include "ResourcePredictEngine.hpp"
using namespace boost;
namespace vesyla {
namespace schedule {
ResourcePredictEngine::ResourcePredictEngine() {}
ResourcePredictEngine::ResourcePredictEngine(Descriptor *desc_) {
  _ptr_desc = desc_;
}
ResourcePredictEngine::~ResourcePredictEngine() {}

bool ResourcePredictEngine::schedule_graph(vector<string> name_list_) {
  CHECK(_ptr_desc);

  // Find out all fetch-issue pairs. It will ignore the nodes that have been
  // marked with "don't-touch".
  std::unordered_map<
      string, std::unordered_map<BIR::Instruction *, pair<string, string>>>
      fetch_issue_pairs;
  fetch_issue_pairs.reserve(10);
  set<string> all_nodes;
  LOG(DEBUG) << "1";
  for (auto &n : name_list_) {
    LOG(DEBUG) <<"2";
    Operation o = _ptr_desc->get_operation(n);
    if (o.children0.size() == 0 && o.children1.size() == 0 && !o.dont_touch) {
      all_nodes.insert(n);
    }
  }
  for (auto &p : _ptr_desc->get_instr_lists()) {
    // if (fetch_issue_pairs.find(p.first) == fetch_issue_pairs.end()) {
    //   fetch_issue_pairs[p.first] = {};
    // }
    for (auto &i : p.second) {
      if (i->timelabels[BIR::Instruction::FETCH_TIME] !=
          i->timelabels[BIR::Instruction::ISSUE_TIME]) {
        string fetch = i->timelabels[BIR::Instruction::FETCH_TIME];
        string issue = i->timelabels[BIR::Instruction::ISSUE_TIME];
        if (all_nodes.find(fetch) != all_nodes.end() &&
            all_nodes.find(issue) != all_nodes.end()) {
          fetch_issue_pairs[p.first][i] = {fetch, issue};
        }
      }
    }
  }

  map<string, map<string, string>> fetch_issue_pair;
  for (auto p : fetch_issue_pairs) {
    fetch_issue_pair[p.first] = {};
    for (auto q : p.second) {
      fetch_issue_pair[p.first][q.second.first] = q.second.second;
    }
  }

  Graph g0, g1;
  map<string, boost::graph_traits<Graph>::vertex_descriptor> gdict0;
  for (auto &v : name_list_) {
    Operation o = _ptr_desc->get_operation(v);
    o.children0 = {};
    gdict0[v] = add_vertex(o, g0);
  }
  vector<Constraint *> list = _ptr_desc->get_all_constraints();
  for (auto &c : list) {
    if (find(name_list_.begin(), name_list_.end(), c->src()) !=
            name_list_.end() &&
        find(name_list_.begin(), name_list_.end(), c->dest()) !=
            name_list_.end()) {
      add_edge(gdict0[c->src()], gdict0[c->dest()], *c, g0);
    }
  }

  // g1 = eliminate_negative_links(g0);
  // if (num_vertices(g1) == 0) {
  //   LOG(DEBUG) << "exit from eliminate negative_links";
  //   return false;
  // }

  // bool flag_changed = false;
  // vector<pair<string, string>> all_added_edges;
  // do {
  //   flag_changed = false;
  //   g1 = predict_order(g1, flag_changed, all_added_edges);
  //   if (num_vertices(g1) == 0) {
  //     LOG(DEBUG) << "exit from predict order";
  //     return false;
  //   }
  // } while (flag_changed);

  // vector<string> all_operation_names = _ptr_desc->get_all_operation_names();
  // for (auto &p : all_added_edges) {
  //   if (std::find(all_operation_names.begin(), all_operation_names.end(),
  //                 p.first) != all_operation_names.end() &&
  //       std::find(all_operation_names.begin(), all_operation_names.end(),
  //                 p.second) != all_operation_names.end()) {
  //     schedule::Constraint c(p.first, p.second, 1, INT_MAX);
  //     _ptr_desc->add_constraint(c);
  //     add_edge(gdict0[c.src()], gdict0[c.dest()], c, g0);
  //     LOG(DEBUG) << "ADD EDGE " << c.src() << " -> " << c.dest();
  //   }
  // }

  // copy_graph(g0, g1);

  boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
  for (tie(vi, vi_end) = vertices(g0); vi != vi_end; vi++) {
    g0[*vi].scheduled_time = INT_MIN;
  }
  Rot global_rot;
  int min_schedule_time = INT_MAX;
  if (!schedule_graph_e(g0, global_rot, min_schedule_time, fetch_issue_pair)) {
    LOG(DEBUG) << "hood";
    return false;
  }

  for (tie(vi, vi_end) = vertices(g0); vi != vi_end; vi++) {
    _ptr_desc->get_mutable_operation(g0[*vi].name()).scheduled_time =
        g0[*vi].scheduled_time;
    // If the scheduled_time less than 0, it means the vertex is a dummy vertex
    // that don't have any ROT entry. So just force it to be scheduled to clock
    // 0;
    if (_ptr_desc->get_operation(g0[*vi].name()).scheduled_time < 0) {
      _ptr_desc->get_mutable_operation(g0[*vi].name()).scheduled_time = 0;
    }
  }
  return true;
}

bool ResourcePredictEngine::check_graph(vector<string> name_list_) {
  CHECK(_ptr_desc);

  // Find out all fetch-issue pairs. It will ignore the nodes that have been
  // marked with "don't-touch".
  std::unordered_map<
      string, std::unordered_map<BIR::Instruction *, pair<string, string>>>
      fetch_issue_pairs;
  fetch_issue_pairs.reserve(10);
  set<string> all_nodes;
  for (auto &n : name_list_) {
    Operation o = _ptr_desc->get_operation(n);
    if (o.children0.size() == 0 && o.children1.size() == 0 && !o.dont_touch) {
      all_nodes.insert(n);
    }
  }
  for (auto &p : _ptr_desc->get_instr_lists()) {
    if (fetch_issue_pairs.find(p.first) == fetch_issue_pairs.end()) {
      fetch_issue_pairs[p.first] = {};
    }
    for (auto &i : p.second) {
      if (i->timelabels[BIR::Instruction::FETCH_TIME] !=
          i->timelabels[BIR::Instruction::ISSUE_TIME]) {
        string fetch = i->timelabels[BIR::Instruction::FETCH_TIME];
        string issue = i->timelabels[BIR::Instruction::ISSUE_TIME];
        if (all_nodes.find(fetch) != all_nodes.end() &&
            all_nodes.find(issue) != all_nodes.end()) {
          fetch_issue_pairs[p.first][i] = {fetch, issue};
        }
      }
    }
  }

  map<string, map<string, string>> fetch_issue_pair;
  for (auto p : fetch_issue_pairs) {
    fetch_issue_pair[p.first] = {};
    for (auto q : p.second) {
      fetch_issue_pair[p.first][q.second.first] = q.second.second;
    }
  }

  Graph g0, g1;
  map<string, boost::graph_traits<Graph>::vertex_descriptor> gdict0;
  for (auto &v : name_list_) {
    Operation o = _ptr_desc->get_operation(v);
    o.children0 = {};
    gdict0[v] = add_vertex(o, g0);
  }
  vector<Constraint *> list = _ptr_desc->get_all_constraints();
  for (auto &c : list) {
    if (find(name_list_.begin(), name_list_.end(), c->src()) !=
            name_list_.end() &&
        find(name_list_.begin(), name_list_.end(), c->dest()) !=
            name_list_.end()) {
      add_edge(gdict0[c->src()], gdict0[c->dest()], *c, g0);
    }
  }

  boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
  for (tie(vi, vi_end) = vertices(g1); vi != vi_end; vi++) {
    g0[*vi].scheduled_time = INT_MIN;
  }
  if (!check_graph_e(g0, fetch_issue_pair)) {
    return false;
  }
  return true;
}

bool ResourcePredictEngine::schedule_graph_e(
    Graph &g_, Rot &global_rot_in_, int &min_end_time_,
    map<string, map<string, string>> fetch_issue_pair_) {

  // Expand Graph
  ExpandGraph g0;
  std::unordered_map<VD, EXVD> g2g0;
  std::unordered_map<EXVD, VD> g02g;
  std::unordered_map<string, vector<pair<EXVD, EXVD>>> res;
  res = expand(g_, g0, g2g0, g02g);
  map<string, map<EXVD, EXVD>> translated_fetch_issue_pair;
  std::map<string, int> vertex_map;
  VI vi, vi_end;
  for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++) {
    vertex_map[g_[*vi].name()] = g2g0[*vi];
  }

  for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++) {
    Rot rot = g_[*vi].rot;

    // cout << *vi << ":" << endl;
    // cout << g_[*vi].rot.dump();
  }

  for (auto r : fetch_issue_pair_) {
    translated_fetch_issue_pair[r.first] = {};
    for (auto k : r.second) {
      translated_fetch_issue_pair[r.first][vertex_map[k.first]] =
          vertex_map[k.second];
    }
  }

  // enforce a fetch=issue constraint
  for (auto r : translated_fetch_issue_pair) {
    for (auto k : r.second) {
      add_edge(k.second, k.first, ExpandEdgePropertyMap(0), g0);
    }
  }

  EXEI ei, ei_end;
  ExpandGraph g1;
  copy_graph(g0, g1);
  negate(g1);

  if (!is_consistant(g1)) {
    return false;
  }

  ExpandGraph g2;
  bool success;

  int k = 5;
  // LOG(DEBUG) << "HERE 11111";
  // for (auto r : res) {
  //   cout << "res " << r.first << ":";
  //   for (auto f : r.second) {
  //     cout << "(" << f.first << "," << f.second << "), ";
  //   }
  //   cout << endl;
  // }
  tie(g2, success) = predict_a_resource_order(g1, res, k);
  // LOG(DEBUG) << "HERE 22222";
  if (!success) {
    return false;
  }
  negate(g2);

  // Now remove the added constraints for fetch-issue pair
  /**
   * TODO: Solve the inefficiency problem so that we don't have to force
   * fetch-issue pairs to be at the same time.
   */
  // for (auto r : translated_fetch_issue_pair) {
  //   for (auto k : r.second) {
  //     remove_edge(k.second, k.first, g2);
  //   }
  // }

  // for (auto r : res) {
  //   if (r.first == "SEQ_1_0") {
  //     std::set<EXVD> selected;
  //     for (auto f : r.second) {
  //       cout << "(" << f.first << "," << f.second << "), ";
  //       selected.insert(f.first);
  //       selected.insert(f.second);
  //     }
  //     cout << endl;
  //     EXEI ei, ei_end;
  //     for (tie(ei, ei_end) = edges(g2); ei != ei_end; ei++) {
  //       if (selected.find(source(*ei, g2)) != selected.end() &&
  //           selected.find(target(*ei, g2)) != selected.end()) {
  //         cout << source(*ei, g2) << "->" << target(*ei, g2) << " ("
  //              << g2[*ei].weight << ")"
  //              << ", ";
  //       }
  //     }
  //     cout << endl;
  //   }
  // }

  ExpressSolver *m_ex = new ExpressSolver(g2, global_rot_in_, min_end_time_,
                                          1000, translated_fetch_issue_pair);
  Gecode::BAB<ExpressSolver> e_ex(m_ex);
  delete m_ex;
  bool found = false;
  int makespan = INT_MAX;
  ExpressSolver *s_ex = e_ex.next();
  if (s_ex) {
    found = true;
    s_ex->fill_scheduled_time(g_, g2g0);
    cout << s_ex->solution_to_str() << endl;
    s_ex->print();
    makespan = s_ex->get_makespan();
    VI vi, vi_end;
    int i = 0;
    Rot grot = global_rot_in_;
    for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++, i++) {
      grot.merge(g_[*vi].rot, g_[*vi].scheduled_time);
    }

    if (!grot.verify()) {
      LOG(FATAL) << "Illegal ROT:" << endl << grot.dump();
    }
    global_rot_in_ = grot;
    min_end_time_ = makespan;
    delete s_ex;
  }

  // if (!found) {
  //   return false;
  // }

  // OptimalSolver *m_op =
  //     new OptimalSolver(g0, global_rot_in_, min_end_time_, makespan,
  //                       translated_fetch_issue_pair, res);
  // Gecode::BAB<OptimalSolver> e_op(m_op);
  // delete m_op;
  // found = false;
  // makespan = INT_MAX;
  // OptimalSolver *s_op = e_op.next();
  // if (s_op) {
  //   found = true;
  //   s_op->fill_scheduled_time(g_, g2g0);
  //   s_op->print();
  //   makespan = s_op->get_makespan();
  //   VI vi, vi_end;
  //   int i = 0;
  //   Rot grot = global_rot_in_;
  //   for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++, i++) {
  //     grot.merge(g_[*vi].rot, g_[*vi].scheduled_time);
  //   }
  //   CHECK(grot.verify());
  //   global_rot_in_ = grot;
  //   min_end_time_ = makespan;
  //   delete s_op;
  // }

  return found;
}

bool ResourcePredictEngine::check_graph_e(
    Graph &g_, map<string, map<string, string>> fetch_issue_pair_) {

  // Expand Graph
  ExpandGraph g0;
  std::unordered_map<VD, EXVD> g2g0;
  std::unordered_map<EXVD, VD> g02g;
  std::unordered_map<string, vector<pair<EXVD, EXVD>>> res;
  res = expand(g_, g0, g2g0, g02g);
  map<string, map<EXVD, EXVD>> translated_fetch_issue_pair;
  std::map<string, int> vertex_map;
  VI vi, vi_end;
  for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++) {
    vertex_map[g_[*vi].name()] = g2g0[*vi];
  }

  for (auto r : fetch_issue_pair_) {
    translated_fetch_issue_pair[r.first] = {};
    for (auto k : r.second) {
      translated_fetch_issue_pair[r.first][vertex_map[k.first]] =
          vertex_map[k.second];
    }
  }
  // enforce a fetch=issue constraint
  for (auto r : translated_fetch_issue_pair) {
    for (auto k : r.second) {
      add_edge(k.second, k.first, ExpandEdgePropertyMap(0), g0);
    }
  }
  EXEI ei, ei_end;
  ExpandGraph g1;
  copy_graph(g0, g1);
  negate(g1);
  if (!is_consistant(g1)) {
    return false;
  }
  ExpandGraph g2;
  bool success;

  int k = 2;
  tie(g2, success) = predict_a_resource_order(g1, res, k);
  if (!success) {
    return false;
  }

  return true;
}


std::unordered_map<
    string,
    vector<pair<ResourcePredictEngine::EXVD, ResourcePredictEngine::EXVD>>>
ResourcePredictEngine::expand(const Graph g0, ExpandGraph &g1,
                              std::unordered_map<VD, EXVD> &g02g1,
                              std::unordered_map<EXVD, VD> &g12g0) {
  std::unordered_map<string, vector<pair<EXVD, EXVD>>> res;

  int sn_counter = 1;
  std::unordered_map<int, int> sn_translator_g02g1;
  std::unordered_map<int, int> sn_translator_g12g0;
  std::unordered_map<int, int> sn_reference_count;
  std::unordered_map<int, int> sn_lock_vertex;
  std::unordered_map<int, int> sn_key_vertex;

  VI vi, vi_end;
  for (tie(vi, vi_end) = vertices(g0); vi != vi_end; vi++) {
    EXVD vd_init = add_vertex(ExpandVertexPropertyMap(), g1);
    g02g1[*vi] = vd_init;
    g12g0[vd_init] = *vi;

    // Deal with resources
    Rot rot = g0[*vi].rot;

    for (auto r : rot) {
      for (auto fr : r.second) {
        if (fr.type() == schedule::Frame::PERIOD) {
          Frame f = fr;
          EXVD vd0 =
              add_vertex(ExpandVertexPropertyMap(r.first, -sn_counter), g1);
          EXVD vd1 =
              add_vertex(ExpandVertexPropertyMap(r.first, +sn_counter), g1);
          sn_counter++;
          add_edge(vd_init, vd0, ExpandEdgePropertyMap(f.t0), g1);
          add_edge(vd0, vd_init, ExpandEdgePropertyMap(-f.t0), g1);
          add_edge(vd_init, vd1, ExpandEdgePropertyMap(f.t1), g1);
          add_edge(vd1, vd_init, ExpandEdgePropertyMap(-f.t1), g1);
        } else if (fr.type() == schedule::Frame::LOCK) {
          Frame f = fr;
          if (sn_translator_g02g1.find(f.sn) == sn_translator_g02g1.end()) {
            EXVD vd0 =
                add_vertex(ExpandVertexPropertyMap(r.first, -sn_counter), g1);
            sn_translator_g02g1[f.sn] = sn_counter;
            sn_translator_g12g0[sn_counter] = f.sn;
            sn_reference_count[sn_counter] = 0;
            sn_reference_count[sn_counter] -= 1;
            sn_lock_vertex[sn_counter] = vd0;
            sn_counter++;
            add_edge(vd_init, vd0, ExpandEdgePropertyMap(f.t0), g1);
            add_edge(vd0, vd_init, ExpandEdgePropertyMap(-f.t0), g1);

            if (*vi == 8) {
              cout << "ADD EDGE1 " << vd_init << "->" << vd0 << endl;
            }

          } else {
            int sn = sn_translator_g02g1[f.sn];
            sn_reference_count[sn] -= 1;
            EXVD vd0 = add_vertex(ExpandVertexPropertyMap(r.first, -sn), g1);
            sn_lock_vertex[sn] = vd0;
            add_edge(vd_init, vd0, ExpandEdgePropertyMap(f.t0), g1);
            add_edge(vd0, vd_init, ExpandEdgePropertyMap(-f.t0), g1);

            if (*vi == 8) {
              cout << "ADD EDGE2 " << vd_init << "->" << vd0 << endl;
            }
          }
        } else if (fr.type() == schedule::Frame::KEY) {
          Frame f = fr;
          if (sn_translator_g02g1.find(f.sn) == sn_translator_g02g1.end()) {
            EXVD vd0 =
                add_vertex(ExpandVertexPropertyMap(r.first, +sn_counter), g1);
            sn_translator_g02g1[f.sn] = sn_counter;
            sn_translator_g12g0[sn_counter] = f.sn;
            sn_reference_count[sn_counter] = 0;
            sn_reference_count[sn_counter] += 1;
            sn_key_vertex[sn_counter] = vd0;
            sn_counter++;
            add_edge(vd_init, vd0, ExpandEdgePropertyMap(f.t1), g1);
            add_edge(vd0, vd_init, ExpandEdgePropertyMap(-f.t1), g1);
          } else {
            int sn = sn_translator_g02g1[f.sn];
            sn_reference_count[sn] += 1;
            EXVD vd0 = add_vertex(ExpandVertexPropertyMap(r.first, +sn), g1);
            sn_key_vertex[sn] = vd0;
            add_edge(vd_init, vd0, ExpandEdgePropertyMap(f.t1), g1);
            add_edge(vd0, vd_init, ExpandEdgePropertyMap(-f.t1), g1);
          }
        }
      }
    }
  }

  // Create a start (S) and end (E) node for the whole graph. For each node (v)
  // in the graph, there should be an edge S->v and v->E with weight 0.
  EXVD node_s = add_vertex(ExpandVertexPropertyMap(), g1);
  EXVD node_e = add_vertex(ExpandVertexPropertyMap(), g1);
  EXVI exvi, exvi_end;
  for (tie(exvi, exvi_end) = vertices(g1); exvi != exvi_end; exvi++) {
    if (*exvi != node_s && *exvi != node_e) {
      add_edge(node_s, *exvi, ExpandEdgePropertyMap(0), g1);
      add_edge(*exvi, node_e, ExpandEdgePropertyMap(0), g1);
    }
  }

  // scan the sn_reference_count and find all the unbalanced lock-key pair.
  for (auto s : sn_reference_count) {
    if (s.second < 0) {
      EXVD lock = sn_lock_vertex[s.first];
      ExpandVertexPropertyMap m = g1[lock];
      m.pair = lock;
      m.type = -m.type;
      EXVD node_k = add_vertex(m, g1);
      add_edge(node_k, node_e, ExpandEdgePropertyMap(0), g1);
      add_edge(node_e, node_k, ExpandEdgePropertyMap(0), g1);
      g1[lock].pair = node_k;
    } else if (s.second > 0) {
      EXVD key = sn_key_vertex[s.first];
      ExpandVertexPropertyMap m = g1[key];
      m.pair = key;
      m.type = -m.type;
      EXVD node_l = add_vertex(m, g1);
      add_edge(node_l, node_s, ExpandEdgePropertyMap(0), g1);
      add_edge(node_s, node_l, ExpandEdgePropertyMap(0), g1);
      g1[key].pair = node_l;
    }
  }

  EI ei, ei_end;
  for (tie(ei, ei_end) = edges(g0); ei != ei_end; ei++) {
    add_edge(g02g1[source(*ei, g0)], g02g1[target(*ei, g0)],
             ExpandEdgePropertyMap(g0[*ei].d_lo), g1);
    if (g0[*ei].d_hi != INT_MAX) {
      add_edge(g02g1[target(*ei, g0)], g02g1[source(*ei, g0)],
               ExpandEdgePropertyMap(-g0[*ei].d_hi), g1);
    }
  }
  std::unordered_map<string, int> sn_count;
  for (tie(exvi, exvi_end) = vertices(g1); exvi != exvi_end; exvi++) {
    if (g1[*exvi].type < 0) {
      if (sn_count.find(g1[*exvi].resource) != sn_count.end()) {
        sn_count[g1[*exvi].resource]++;
      } else {
        sn_count[g1[*exvi].resource] = 1;
      }
    }
  }
  std::set<string> remove_resource;
  for (auto &r : sn_count) {
    if (r.second <= 1) {
      remove_resource.insert(r.first);
    }
  }
  for (tie(exvi, exvi_end) = vertices(g1); exvi != exvi_end; exvi++) {
    if (remove_resource.find(g1[*exvi].resource) != remove_resource.end()) {
      g1[*exvi].resource = "";
      g1[*exvi].type = 0;
    }
  }

  std::unordered_map<int, pair<EXVD, EXVD>> sn_translator;
  std::unordered_map<string, set<int>> res_translator;
  for (tie(exvi, exvi_end) = vertices(g1); exvi != exvi_end; exvi++) {
    if (g1[*exvi].resource == "") {
      continue;
    }
    int sn = g1[*exvi].type;
    bool is_lock = (sn < 0);
    sn = abs(sn);
    if (sn_translator.find(sn) == sn_translator.end()) {
      sn_translator[sn] = {0, 0};
    }
    if (res_translator.find(g1[*exvi].resource) == res_translator.end()) {
      res_translator[g1[*exvi].resource] = {};
    }
    res_translator[g1[*exvi].resource].insert(sn);
    if (is_lock) {
      sn_translator[sn].first = *exvi;
    } else {
      sn_translator[sn].second = *exvi;
    }
  }
  for (auto &r : res_translator) {
    res[r.first] = {};
    for (auto &sn : r.second) {
      res[r.first].push_back(sn_translator[sn]);
    }
  }

  for (auto &r : res) {
    for (auto &s : r.second) {
      g1[s.first].pair = s.second;
    }
  }

  for (auto &r : res) {
    for (auto &s : r.second) {
      g1[s.first].pair = s.second;
    }
  }

  return res;
}

void ResourcePredictEngine::negate(ExpandGraph &g) {
  EXEI ei, ei_end;
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ei++) {
    g[*ei].weight = -g[*ei].weight;
  }
}

bool ResourcePredictEngine::is_consistant(ExpandGraph &g) {
  // custom bellman-ford algorithm to check negative weighted cycles. The BGL
  // version of BF algorithm is so complex.
  EXVI vi, vi_end;

  for (tie(vi, vi_end) = vertices(g); vi != vi_end; vi++) {

    EXVI vvi, vvi_end;
    std::unordered_map<EXVD, int> distance;
    for (tie(vvi, vvi_end) = vertices(g); vvi != vvi_end; vvi++) {
      if (*vvi == *vi) {
        distance[*vvi] = 0;
      } else {
        distance[*vvi] = INT_MAX;
      }
    }

    for (auto i = 0; i < num_vertices(g) - 1; i++) {
      bool flag_changed = false;
      EXEI ei, ei_end;
      for (tie(ei, ei_end) = edges(g); ei != ei_end; ei++) {
        EXVD src, dest;
        src = source(*ei, g);
        dest = target(*ei, g);
        if (distance[src] != INT_MAX &&
            distance[dest] > (distance[src] + g[*ei].weight)) {
          flag_changed = true;
          distance[dest] = distance[src] + g[*ei].weight;
        }
      }
      if (!flag_changed) {
        break;
      }
    }

    // Last round, if there is still changes, it must contain at least one
    // negtive weighted cycle.
    EXEI ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ei++) {
      EXVD src, dest;
      src = source(*ei, g);
      dest = target(*ei, g);
      if (distance[src] != INT_MAX &&
          distance[dest] > (distance[src] + g[*ei].weight)) {
        return false;
      }
    }
  }

  return true;
}

std::unordered_map<ResourcePredictEngine::EXVD, int>
ResourcePredictEngine::bellman_ford_shortest_path(ExpandGraph g, EXVD start) {

  // custom bellman-ford algorithm to check negative weighted cycles. The BGL
  // version of BF algorithm is so complex.

  EXVI vi, vi_end;
  std::unordered_map<EXVD, int> distance;
  for (tie(vi, vi_end) = vertices(g); vi != vi_end; vi++) {
    if (*vi == start) {
      distance[*vi] = 0;
    } else {
      distance[*vi] = INT_MAX;
    }
  }

  for (auto i = 0; i < num_vertices(g) - 1; i++) {
    bool flag_changed = false;
    EXEI ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ei++) {
      EXVD src, dest;
      src = source(*ei, g);
      dest = target(*ei, g);
      if (distance[src] != INT_MAX &&
          distance[dest] > (distance[src] + g[*ei].weight)) {
        flag_changed = true;
        distance[dest] = distance[src] + g[*ei].weight;
      }
    }
    if (!flag_changed) {
      break;
    }
  }

  // Last round, if there is still changes, it must contain at least one
  // negtive weighted cycle.
  bool flag_changed = false;
  EXEI ei, ei_end;
  for (tie(ei, ei_end) = edges(g); ei != ei_end; ei++) {
    EXVD src, dest;
    src = source(*ei, g);
    dest = target(*ei, g);
    if (distance[src] != INT_MAX &&
        distance[dest] > (distance[src] + g[*ei].weight)) {
      flag_changed = true;
      distance[dest] = distance[src] + g[*ei].weight;
    }
  }
  if (flag_changed) {
    LOG(FATAL) << "Unbounded shortest path!";
  }

  vector<EXVD> removed_element;
  for (auto d : distance) {
    if (d.second == INT_MAX) {
      removed_element.push_back(d.first);
    }
  }
  for (auto &e : removed_element) {
    distance.erase(e);
  }
  return distance;
}

std::unordered_map<ResourcePredictEngine::EXVD, int>
ResourcePredictEngine::find_successors(ExpandGraph g, EXVD start) {
  std::unordered_map<EXVD, int> distance = bellman_ford_shortest_path(g, start);
  vector<EXVD> removed_element;
  for (auto d : distance) {
    if (d.second >= 0 && d.first != start) {
      removed_element.push_back(d.first);
    }
  }
  for (auto &e : removed_element) {
    distance.erase(e);
  }
  return distance;
}

pair<ResourcePredictEngine::ExpandGraph, bool>
ResourcePredictEngine::predict_a_resource_order(
    ExpandGraph g0, std::unordered_map<string, vector<pair<VD, VD>>> res,
    int k) {

  if (res.empty()) {
    return {g0, true};
  }

  vector<pair<string, vector<pair<VD, VD>>>> ordered_res;
  for (auto &r : res) {
    ordered_res.push_back({r.first, r.second});
  }
  sort(ordered_res.begin(), ordered_res.end(),
       [](pair<string, vector<pair<VD, VD>>> a,
          pair<string, vector<pair<VD, VD>>> b) {
         return a.second.size() < b.second.size();
       });
  ExpandGraph null_graph;
  auto r = ordered_res[0];
  vector<pair<VD, VD>> pairs = r.second;

  if (pairs.size() <= 1) {
    return {g0, true};
  }

  boost::adjacency_list<vecS, vecS, bidirectionalS> gg(pairs.size());
  for (auto i = 0; i < pairs.size(); i++) {
    std::unordered_map<EXVD, int> successors =
        find_successors(g0, pairs[i].first);
    for (auto j = 0; j < pairs.size(); j++) {

      if (i == j) {
        continue;
      }
      if (successors.find(pairs[j].second) != successors.end()) {
        add_edge(i, j, gg);
      }
    }
  }

  // Check if gg is a DAG
  if (bglex::simple_cycles(gg).size() > 0) {
    return {g0, false};
  }

  bool is_unique;
  vector<vector<VD>> kts;

  tie(kts, is_unique) = k_random_topological_sorts(gg, k);
  for (auto ts : kts) {
    ExpandGraph g1;
    copy_graph(g0, g1);

    for (auto i = 0; i < ts.size() - 1; i++) {
      VD src = ts[i];
      VD dest = ts[i + 1];
      if (!(edge(pairs[src].second, pairs[dest].first, g1).second) ||
          g1[edge(pairs[src].second, pairs[dest].first, g1).first].weight >
              -1) {
        add_edge(pairs[src].second, pairs[dest].first,
                 ExpandEdgePropertyMap(-1), g1);

        if (!is_consistant(g1)) {
          add_edge(pairs[dest].second, pairs[src].first,
                   ExpandEdgePropertyMap(-1), g0);
          if (!is_consistant(g0)) {
            return {null_graph, false};
          }
          return predict_a_resource_order(g0, res, k);
        }
      }
    }
    std::unordered_map<string, vector<pair<VD, VD>>> new_res = res;
    new_res.erase(r.first);
    ExpandGraph g2;
    bool success;
    tie(g2, success) = predict_a_resource_order(g1, new_res, k);
    if (success) {
      return {g2, true};
    }
  }
  return {null_graph, false};
}

int ResourcePredictEngine::min_topologic_sorts_count(ExpandGraph g) {
  // The lower bound is given by the product of node number in each layer of the
  // DAG.

  ExpandGraph g1;
  copy_graph(g, g1);
  vector<vector<EXVD>> layers;
  std::unordered_map<EXVD, bool> visited;
  EXVI vi, vi_end;
  for (int i = 0; i < num_vertices(g1); i++) {
    if (visited.size() >= num_vertices(g1)) {
      break;
    }
    vector<EXVD> layer;
    for (tie(vi, vi_end) = vertices(g1); vi != vi_end; vi++) {
      if (in_degree(*vi, g1) == 0 && visited[*vi] == false) {
        visited[*vi] = true;
        layer.push_back(*vi);
      }
    }
    for (auto vd : layer) {
      clear_out_edges(vd, g1);
    }
    layers.push_back(layer);
  }

  int count = 1;
  for (auto l : layers) {
    count *= layers.size();
  }
  return count;
}

pair<vector<vector<boost::adjacency_list<
         boost::vecS, boost::vecS, boost::bidirectionalS>::vertex_descriptor>>,
     bool>
ResourcePredictEngine::k_random_topological_sorts(
    boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> g,
    int k) {
  int factorial_n = 1;
  for (auto i = 1; i <= num_vertices(g); i++) {
    factorial_n *= i;
    if (k < factorial_n) {
      break;
    }
  }
  if (k > factorial_n) {
    k = factorial_n;
  }
  vector<vector<boost::adjacency_list<
      boost::vecS, boost::vecS, boost::bidirectionalS>::vertex_descriptor>>
      kts;
  int max_trial_count = 5 * k;
  for (auto i = 0; i < max_trial_count; i++) {
    bool is_unique = true;

    vector<boost::adjacency_list<boost::vecS, boost::vecS,
                                 boost::bidirectionalS>::vertex_descriptor>
        ts = bglex::random_topological_sort(g, is_unique);

    if (is_unique) {
      return {{ts}, true};
    }
    bool flag_same = false;
    for (auto v : kts) {
      bool flag_same_2 = true;
      for (int j = 0; j < v.size(); j++) {
        if (v[j] != ts[j]) {
          flag_same_2 = false;
          break;
        }
      }
      if (flag_same_2) {
        flag_same = true;
      }
      if (flag_same == true) {
        break;
      }
    }
    if (flag_same == false) {
      kts.push_back(ts);
    }
    if (kts.size() >= k) {
      return {kts, false};
    }
  }
  return {kts, false};
}

/*******************************************************************************
 * ExpressSolver
 ******************************************************************************/

ResourcePredictEngine::ExpressSolver::ExpressSolver(
    ExpandGraph &g_, Rot &global_rot_in_, int &min_end_time_,
    int max_scheduled_time,
    map<string, map<EXVD, EXVD>> translated_fetch_issue_pair_)
    : _scheduled_time_list(*this, num_vertices(g_), -max_scheduled_time,
                           max_scheduled_time),
      _makespan(*this, 0, max_scheduled_time) {

  ResourcePredictEngine::EXVI vi, vi_end;
  int i = 0;
  for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++, i++) {
    _vertex_map[*vi] = i;
    if (g_[*vi].resource != "") {
      Gecode::rel(*this, _scheduled_time_list[i] >= 0);
    }
  }

  // Cost function
  Gecode::max(*this, _scheduled_time_list, _makespan);

  // post edge dependencies
  ResourcePredictEngine::EXEI ei, ei_end;
  for (tie(ei, ei_end) = edges(g_); ei != ei_end; ei++) {
    ResourcePredictEngine::EXVD src_name = source(*ei, g_);
    ResourcePredictEngine::EXVD dest_name = target(*ei, g_);
    int src_idx = _vertex_map[src_name];
    int dest_idx = _vertex_map[dest_name];

    Gecode::rel(*this, _scheduled_time_list[dest_idx] -
                               _scheduled_time_list[src_idx] >=
                           g_[*ei].weight);
  }

  // post fetch - issue constraints 
  for (auto &pp : translated_fetch_issue_pair_) {
    auto fip = pp.second;
    if (fip.empty()) {
      continue;
    }
    Gecode::IntVarArgs fetch_array(*this, fip.size(), 0, max_scheduled_time);
    Gecode::IntVarArgs issue_array(*this, fip.size(), 0, max_scheduled_time);
    i = 0;
    for (auto &pair : fip) {
      int v_src = _vertex_map[pair.first];
      int v_desc = _vertex_map[pair.second];
      Gecode::rel(*this, fetch_array[i] == _scheduled_time_list[v_src]);
      Gecode::rel(*this, issue_array[i] == _scheduled_time_list[v_desc]);
      i++;
    }
    for (int x = 0; x < fetch_array.size(); x++) {
      for (int y = 0; y < issue_array.size(); y++) {
        Gecode::rel(*this, !(fetch_array[x] <= issue_array[y] &&
                             issue_array[x] > issue_array[y]));
      }
    }
    for (int x = 0; x < issue_array.size(); x++) {
      Gecode::count(*this, fetch_array, issue_array[x], Gecode::IRT_EQ, 1,
                    Gecode::IPL_DEF);
    }

    Gecode::BoolVarArgs connect_map(*this, fip.size() * fip.size(), 0, 1);
    Gecode::IntVarArgs n(*this, fip.size(), 0, max_scheduled_time);

    Gecode::Matrix<Gecode::BoolVarArgs> mat(connect_map, fip.size(),
                                            fip.size());
    for (int i = 0; i < fip.size(); i++) {
      Gecode::IntVarArgs s(*this, fip.size(), 0, max_scheduled_time);
      for (int j = 0; j < fip.size(); j++) {
        Gecode::rel(*this, issue_array[i], Gecode::IRT_EQ, issue_array[j],
                    mat(i, j));
        Gecode::rel(*this, s[j] == mat(i, j) * fetch_array[j]);
      }

      Gecode::rel(*this, Gecode::sum(mat.row(i)) == n[i]);

      Gecode::rel(*this, Gecode::sum(s) ==
                             n[i] * issue_array[i] - n[i] * (n[i] - 1) / 2);
    }
  }

  // post branching
  Gecode::branch(*this, _scheduled_time_list, Gecode::INT_VAR_MIN_MIN(),
                 Gecode::INT_VAL_SPLIT_MIN());
}

// search support functions
ResourcePredictEngine::ExpressSolver::ExpressSolver(ExpressSolver &s)
    : Gecode::IntMinimizeSpace(s) {
  _scheduled_time_list.update(*this, s._scheduled_time_list);
  _vertex_map = s._vertex_map;
  _makespan.update(*this, s._makespan);
}
Gecode::Space *ResourcePredictEngine::ExpressSolver::copy(void) {
  return new ExpressSolver(*this);
}
string ResourcePredictEngine::ExpressSolver::solution_to_str(void) const {
  std::stringstream buffer;
  buffer << _scheduled_time_list;
  return buffer.str();
}
Gecode::IntVar ResourcePredictEngine::ExpressSolver::cost(void) const {
  return _makespan;
}
void ResourcePredictEngine::ExpressSolver::print(void) const {
  cout << "makespan = " << _makespan.min() << endl;
  // for (auto k : _vertex_map) {
  //   cout << k.first << " = " << _scheduled_time_list[k.second] << endl;
  // }
}
int ResourcePredictEngine::ExpressSolver::get_makespan(void) const {
  return _makespan.min();
}
void ResourcePredictEngine::ExpressSolver::constrain(const Gecode::Space &b_) {
  const ExpressSolver &b = static_cast<const ExpressSolver &>(b_);
  Gecode::rel(*this, _makespan < b._makespan);
}
void ResourcePredictEngine::ExpressSolver::fill_scheduled_time(
    Graph &g_, std::unordered_map<VD, EXVD> g2g0_) {
  Graph::vertex_iterator vi, vi_end;
  for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++) {
    EXVD g0_vd = g2g0_[*vi];
    int id = _vertex_map[g0_vd];
    g_[*vi].scheduled_time = _scheduled_time_list[id].val();
    // cout << "g_[" << *vi << "] = g0[" << g0_vd << "] = cycle "
    //      << _scheduled_time_list[id].val() << endl;
  }
}

/*******************************************************************************
 * OptimalSolver
 ******************************************************************************/

ResourcePredictEngine::OptimalSolver::OptimalSolver(
    ExpandGraph &g_, Rot &global_rot_in_, int &min_end_time_,
    int max_scheduled_time,
    map<string, map<EXVD, EXVD>> translated_fetch_issue_pair_,
    std::unordered_map<string, vector<pair<EXVD, EXVD>>> res_)
    : _scheduled_time_list(*this, num_vertices(g_), 0, max_scheduled_time),
      _makespan(*this, 0, max_scheduled_time) {

  ResourcePredictEngine::EXVI vi, vi_end;
  int i = 0;
  for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++, i++) {
    _vertex_map[*vi] = i;
    if (g_[*vi].resource != "") {
      Gecode::rel(*this, _scheduled_time_list[i] >= 0);
    }
  }

  // Cost function
  Gecode::max(*this, _scheduled_time_list, _makespan);

  // post edge dependencies
  ResourcePredictEngine::EXEI ei, ei_end;
  for (tie(ei, ei_end) = edges(g_); ei != ei_end; ei++) {
    ResourcePredictEngine::EXVD src_name = source(*ei, g_);
    ResourcePredictEngine::EXVD dest_name = target(*ei, g_);
    int src_idx = _vertex_map[src_name];
    int dest_idx = _vertex_map[dest_name];

    Gecode::rel(*this, _scheduled_time_list[dest_idx] -
                               _scheduled_time_list[src_idx] >=
                           g_[*ei].weight);
  }

  // post fetch - issue constraints
  for (auto &pp : translated_fetch_issue_pair_) {
    auto fip = pp.second;
    if (fip.empty()) {
      continue;
    }
    Gecode::IntVarArgs fetch_array(*this, fip.size(), 0, max_scheduled_time);
    Gecode::IntVarArgs issue_array(*this, fip.size(), 0, max_scheduled_time);
    i = 0;
    for (auto &pair : fip) {
      int v_src = _vertex_map[pair.first];
      int v_desc = _vertex_map[pair.second];
      Gecode::rel(*this, fetch_array[i] == _scheduled_time_list[v_src]);
      Gecode::rel(*this, issue_array[i] == _scheduled_time_list[v_desc]);
      i++;
    }
    for (int x = 0; x < fetch_array.size(); x++) {
      for (int y = 0; y < issue_array.size(); y++) {
        Gecode::rel(*this, !(fetch_array[x] <= issue_array[y] &&
                             issue_array[x] > issue_array[y]));
      }
    }
    for (int x = 0; x < issue_array.size(); x++) {
      Gecode::count(*this, fetch_array, issue_array[x], Gecode::IRT_EQ, 1,
                    Gecode::IPL_DEF);
    }

    Gecode::BoolVarArgs connect_map(*this, fip.size() * fip.size(), 0, 1);
    Gecode::IntVarArgs n(*this, fip.size(), 0, max_scheduled_time);

    Gecode::Matrix<Gecode::BoolVarArgs> mat(connect_map, fip.size(),
                                            fip.size());
    for (int i = 0; i < fip.size(); i++) {
      Gecode::IntVarArgs s(*this, fip.size(), 0, max_scheduled_time);
      for (int j = 0; j < fip.size(); j++) {
        Gecode::rel(*this, issue_array[i], Gecode::IRT_EQ, issue_array[j],
                    mat(i, j));
        Gecode::rel(*this, s[j] == mat(i, j) * fetch_array[j]);
      }

      Gecode::rel(*this, Gecode::sum(mat.row(i)) == n[i]);

      Gecode::rel(*this, Gecode::sum(s) ==
                             n[i] * issue_array[i] - n[i] * (n[i] - 1) / 2);
    }
  }

  // post resource conflict constraints
  for (auto r : res_) {
    auto pairs = r.second;
    int num_pairs = pairs.size();
    Gecode::IntVarArgs start(*this, num_pairs, 0, max_scheduled_time);
    Gecode::IntVarArgs end(*this, num_pairs, 0, max_scheduled_time);
    Gecode::IntVarArgs delay(*this, num_pairs, 0, max_scheduled_time);
    for (auto i = 0; i < num_pairs; i++) {
      Gecode::rel(*this, delay[i] == end[i] - start[i]);
      Gecode::rel(*this, start[i] == _scheduled_time_list[pairs[i].first]);
      Gecode::rel(*this, end[i] == _scheduled_time_list[pairs[i].second] + 1);
    }
    Gecode::unary(*this, start, delay, end, Gecode::IPL_DEF);
  }

  // post branching
  Gecode::branch(*this, _scheduled_time_list, Gecode::INT_VAR_MIN_MIN(),
                 Gecode::INT_VAL_SPLIT_MIN());
}

// search support functions
ResourcePredictEngine::OptimalSolver::OptimalSolver(OptimalSolver &s)
    : Gecode::IntMinimizeSpace(s) {
  _scheduled_time_list.update(*this, s._scheduled_time_list);
  _vertex_map = s._vertex_map;
  _makespan.update(*this, s._makespan);
}
Gecode::Space *ResourcePredictEngine::OptimalSolver::copy(void) {
  return new OptimalSolver(*this);
}
string ResourcePredictEngine::OptimalSolver::solution_to_str(void) const {
  std::stringstream buffer;
  buffer << _scheduled_time_list;
  return buffer.str();
}
Gecode::IntVar ResourcePredictEngine::OptimalSolver::cost(void) const {
  return _makespan;
}
void ResourcePredictEngine::OptimalSolver::print(void) const {
  cout << "makespan = " << _makespan.min() << endl;
}
int ResourcePredictEngine::OptimalSolver::get_makespan(void) const {
  return _makespan.min();
}
void ResourcePredictEngine::OptimalSolver::constrain(const Gecode::Space &b_) {
  const OptimalSolver &b = static_cast<const OptimalSolver &>(b_);
  Gecode::rel(*this, _makespan < b._makespan);
}
void ResourcePredictEngine::OptimalSolver::fill_scheduled_time(
    Graph &g_, std::unordered_map<VD, EXVD> g2g0_) {
  Graph::vertex_iterator vi, vi_end;
  for (tie(vi, vi_end) = vertices(g_); vi != vi_end; vi++) {
    EXVD g0_vd = g2g0_[*vi];
    int id = _vertex_map[g0_vd];
    g_[*vi].scheduled_time = _scheduled_time_list[id].val();
  }
}

} // namespace schedule
} // namespace vesyla
