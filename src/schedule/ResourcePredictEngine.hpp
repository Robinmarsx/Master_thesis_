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

#ifndef __VESYLA_SCHEDULE_RESOURCE_PREDICT_ENGINE_HPP__
#define __VESYLA_SCHEDULE_RESOURCE_PREDICT_ENGINE_HPP__

#include "Engine.hpp"
#include <gecode/int.hh>
#include <gecode/kernel.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/copy.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_utility.hpp>

#include "util/bglex/random_topological_sorts.hpp"
#include "util/bglex/simple_cycles.hpp"

namespace vesyla {
namespace schedule {
/**
 * \brief Scheduling Engine that explores the design space by predicting
 * resource order.
 */
class ResourcePredictEngine : public Engine {
public:
  struct ExpandVertexPropertyMap {
    string resource;
    int type;
    int pair;
    ExpandVertexPropertyMap(string resource_ = "", int type_ = 0,
                            int pair_ = -1) {
      resource = resource_;
      type = type_;
      pair = pair_;
    }
  };
  struct ExpandEdgePropertyMap {
    int weight;
    ExpandEdgePropertyMap(int weight_ = 0) { weight = weight_; }
  };
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS,
                                ExpandVertexPropertyMap, ExpandEdgePropertyMap>
      ExpandGraph;
  typedef Graph::vertex_descriptor VD;
  typedef Graph::vertex_iterator VI;
  typedef Graph::edge_descriptor ED;
  typedef Graph::edge_iterator EI;
  typedef Graph::in_edge_iterator IEI;
  typedef Graph::out_edge_iterator OEI;
  typedef ExpandGraph::vertex_descriptor EXVD;
  typedef ExpandGraph::vertex_iterator EXVI;
  typedef ExpandGraph::edge_descriptor EXED;
  typedef ExpandGraph::edge_iterator EXEI;
  typedef ExpandGraph::in_edge_iterator EXIEI;
  typedef ExpandGraph::out_edge_iterator EXOEI;

public:
  ResourcePredictEngine();
  ResourcePredictEngine(Descriptor *ptr_desc_);
  ~ResourcePredictEngine();

public:
  /**
   * Schedule the graph.
   */
  bool schedule_graph(vector<string> name_list_);
  /**
   * Quickly check the if the graph is schedulable/
   */
  bool check_graph(vector<string> name_list_);

private:
  bool schedule_graph_e(Graph &g_, Rot &global_rot_in_, int &min_end_time_,
                        map<string, map<string, string>> fetch_issue_pair_);
  bool check_graph_e(Graph &g_,
                     map<string, map<string, string>> fetch_issue_pair_);

private:
  std::unordered_map<string, vector<pair<EXVD, EXVD>>>
  expand(const Graph g0, ExpandGraph &g1, std::unordered_map<VD, EXVD> &g02g1,
         std::unordered_map<EXVD, VD> &g12g0);
  void negate(ExpandGraph &g);
  bool is_consistant(ExpandGraph &g);
  std::unordered_map<EXVD, int> bellman_ford_shortest_path(ExpandGraph g,
                                                           EXVD start);
  std::unordered_map<EXVD, int> find_successors(ExpandGraph g, EXVD start);
  pair<ExpandGraph, bool>
  predict_a_resource_order(ExpandGraph g0,
                           std::unordered_map<string, vector<pair<VD, VD>>> res,
                           int k = 5);
  /**
   * Calculate the lower bound of the topological sort count for a given DAG
   */
  int min_topologic_sorts_count(ExpandGraph g);
  pair<
      vector<vector<boost::adjacency_list<
          boost::vecS, boost::vecS, boost::bidirectionalS>::vertex_descriptor>>,
      bool>
  k_random_topological_sorts(
      boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> g,
      int k);

  /**
   * The coarse-grain solver that explore the whole space and find the
   * optimal solution under some extra hierustic constraints that are
   * arbitarily decided in order to just quickly find one valid solution and
   * constraint the domain of more fine-grained OptimalSolver.
   */
public:
  class ExpressSolver : public Gecode::IntMinimizeSpace {
  protected:
    Gecode::IntVarArray _scheduled_time_list;
    Gecode::IntVar _makespan;
    std::unordered_map<EXVD, int> _vertex_map;

  public:
    ExpressSolver(ExpandGraph &g_, Rot &global_rot_in_, int &min_end_time_,
                  int max_scheduled_time,
                  map<string, map<EXVD, EXVD>> translated_fetch_issue_pair_);
    ExpressSolver(ExpressSolver &s);
    virtual Gecode::Space *copy(void);
    string solution_to_str(void) const;
    void fill_scheduled_time(Graph &g_, std::unordered_map<VD, EXVD> g2g0_);
    virtual Gecode::IntVar cost(void) const;
    void print(void) const;
    int get_makespan(void) const;
    virtual void constrain(const Gecode::Space &b_);
  };

  /**
   * The fine-grain solver that actually explores the whole space and find the
   * optimal solution. It's domain is constrained by the solution found by
   * ExpressSolver.
   */
public:
  class OptimalSolver : public Gecode::IntMinimizeSpace {
  protected:
    Gecode::IntVarArray _scheduled_time_list;
    Gecode::IntVar _makespan;
    std::unordered_map<EXVD, int> _vertex_map;

  public:
    OptimalSolver(ExpandGraph &g_, Rot &global_rot_in_, int &min_end_time_,
                  int max_scheduled_time,
                  map<string, map<EXVD, EXVD>> translated_fetch_issue_pair_,
                  std::unordered_map<string, vector<pair<EXVD, EXVD>>> res_);
    OptimalSolver(OptimalSolver &s);
    virtual Gecode::Space *copy(void);
    string solution_to_str(void) const;
    void fill_scheduled_time(Graph &g_, std::unordered_map<VD, EXVD> g2g0_);
    virtual Gecode::IntVar cost(void) const;
    void print(void) const;
    int get_makespan(void) const;
    virtual void constrain(const Gecode::Space &b_);
  };
};

// Here start define the real solver class
class ResourcePredictEngineSolver : public Gecode::IntMinimizeSpace {
protected:
  Gecode::IntVarArray _scheduled_time_list;
  Gecode::IntVar _latency;
  std::unordered_map<ResourcePredictEngine::EXVD, int> _vertex_map;

public:
  ResourcePredictEngineSolver(
      ResourcePredictEngine::ExpandGraph &g_, Rot &global_rot_in_,
      int &min_end_time_, int max_scheduled_time,
      map<string, map<ResourcePredictEngine::EXVD, ResourcePredictEngine::EXVD>>
          translated_fetch_issue_pair_);
  ResourcePredictEngineSolver(ResourcePredictEngineSolver &s);
  virtual Gecode::Space *copy(void);
  string solution_to_str(void) const;
  void fill_scheduled_time(
      Graph &g_,
      std::unordered_map<Graph::vertex_descriptor, ResourcePredictEngine::EXVD>
          g2g0_);
  virtual Gecode::IntVar cost(void) const;
  void print(void) const;
  virtual void constrain(const Gecode::Space &b_);
};

} // namespace schedule
} // namespace vesyla

#endif // __VESYLA_SCHEDULE_CONSTRAINT_PROGRAMMING_ENGINE_HPP__
