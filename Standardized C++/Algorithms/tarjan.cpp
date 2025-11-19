#include <bits/stdc++.h>
using namespace std;


vector<vector<uint32_t>> find_all_strongly_connected_components(const vector<vector<uint32_t>>& graph, const uint32_t& n)
{
    // Stack frame for recursion simulator in the stack
    struct stack_frame
    {
        uint32_t it;
        std::vector<uint32_t>::const_iterator successor_it;
        std::vector<uint32_t>::const_iterator successors_end;
        bool visited;
        stack_frame(const uint32_t _node_id, const std::vector<uint32_t>::const_iterator _begin,
        const std::vector<uint32_t>::const_iterator _end, const bool _visited)
        : it(_node_id), successor_it(_begin), successors_end(_end), visited(_visited) {}
    };
    // Map each node to its index in the search order
    unordered_map<uint32_t, uint32_t> node_index;
    unordered_map<uint32_t, uint32_t> node_lowlink;
    // Set of nodes that have been visited
    unordered_set<uint32_t> visited_nodes;
    // Stack to store the data of current nodes
    std::stack<uint32_t> data_stack;
    // Set to quickly check if a node is on the DFS stack
    unordered_set<uint32_t> on_stack;
    // Current index used in ordering DFS traversal
    uint32_t current_index = 0;
    // Vector to store all Strongly Connected Components found
    vector<vector<uint32_t>> sccs;
    vector<uint32_t> scc;
    sccs.reserve(n);
    node_index.reserve(n);
    node_lowlink.reserve(n);
    visited_nodes.reserve(n);
    
    // Iterate over all nodes in the graph
    for (uint32_t it = 0; it < n; ++it)
    {
        if (visited_nodes.find(it) == visited_nodes.end())
        {
            // Stack to simulate recursive DFS iteratively
            std::stack<stack_frame> dfs_stack;

            // Start from the current node 
            const auto& successors = graph[it];
            dfs_stack.emplace(it, successors.begin(), successors.end(), false);
            while (!dfs_stack.empty())
            {
                stack_frame& current_frame = dfs_stack.top();
                uint32_t current_node = current_frame.it;
                bool has_successors = false; // Controls the recursion flow

                // First time visiting this node
                if (!current_frame.visited)
                {
                    node_index[current_node] = current_index;
                    node_lowlink[current_node] = current_index;
                    ++current_index;
                    visited_nodes.emplace(current_node);
                    data_stack.emplace(current_node);
                    on_stack.insert(current_node);
                    current_frame.visited = true;
                }
                // Process all successors of the current node
                while (current_frame.successor_it != current_frame.successors_end)
                {
                    uint32_t successor_node = *(current_frame.successor_it++);
                    if (visited_nodes.find(successor_node) == visited_nodes.end())
                    {
                        // Successor node has not been visited; recurse on it
                        const auto& successor_successors = graph[successor_node];
                        dfs_stack.emplace(successor_node, successor_successors.begin(), successor_successors.end(), false);
                        has_successors = true;
                        break; // Pause processing current node for the next node
                    }
                    else if (on_stack.find(successor_node) != on_stack.end())
                    {
                        // If node has been visited is still on the stack, update the current's lowlink with that node
                        node_lowlink[current_node] = std::min(node_lowlink[current_node], node_index[successor_node]);
                    }
                }

                // So that if a successor was being emplaced it skips the popping
                if (has_successors)
                {
                    continue;
                }

                // Found a root node of a component if lowlink is same as the index
                if (node_lowlink[current_node] == node_index[current_node])
                {
                    // Start popping off the data stack
                    unordered_set<uint32_t> current_component;
                    uint32_t count = 0;
                    uint32_t top_node;
                    do
                    {
                        top_node = data_stack.top();
                        data_stack.pop();
                        on_stack.erase(top_node);
                        current_component.emplace(top_node);
                        scc.emplace_back(top_node);
                        ++count;
                    } while (top_node != current_node);
                    sccs.emplace_back(scc);
                    scc.clear();
                    
                }
                dfs_stack.pop();
                if (!dfs_stack.empty())
                {
                    // Update the lowlink value of the parent node potentially
                    uint32_t parent_node = dfs_stack.top().it;
                    node_lowlink[parent_node] = std::min(node_lowlink[parent_node], node_lowlink[current_node]);
                }
            }
        }
    }

    return sccs;
}
