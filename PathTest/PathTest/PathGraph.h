#ifndef PathGraph_h
#define PathGraph_h
#include <list>
#include <map>
#include <unordered_map>
#include "PathError.h"
#include "stringTrim.h"

/** Undirected acyclic graph */
class PathGraph
{
public:
    /** adjacency list*/
    using Adj = std::map<std::string, std::list<std::string>>;
    PathGraph()
    :m {0} {}
    
    //==========================================================
    /** add node (location) */
    bool addNode (const std::string& node)
    {
        if (! nodeExists (node))
        {
            adjList[node];
            return true;
        }
        return false;
    }
    
    /** add edge (path) */
    bool addEdge (const std::string& source, const std::string& target)
    {
        if (! nodeExists (source) || ! nodeExists (target) )
            return false;
        adjList[source].push_back (target);
        adjList[target].push_back (source);
        ++m;
        return true;
    }
    
    //==========================================================
    std::list<std::string> findPath (const std::string& origin, const std::string& destination)
    {
        /** argument constrains:
         - 1 to 170 alpha characters or white space*/
        if (! isArgumentValid (origin) || ! isArgumentValid (destination))
            throw IllegalArgument();
        if (! isPathAvailable (origin, destination))
            throw PathNotFound (origin, destination);
        std::list<std::string> stops;
        /** to be implemented. */
        return stops;
    }
    
    /** check if destination is reachable. BFS algorithm is used*/
    bool isPathAvailable (const std::string& origin, const std::string& destination)
    {
        /** this is to be called in findPath() after arguments checking, so arguments must be valid. */
        /** at least one node exist, it must be source. */
        if (origin == destination)
            return true;
        
        bool res = BFS (origin, destination);
        return res;
    }
    
    bool isArgumentValid (const std::string& location)
    {
        /** empty string. */
        std::string s = location;
        ltrim (s);
        rtrim (s);
        if (s.begin() == s.end())
            return false;
        auto p = std::find_if (s.begin(), s.end(), [] (char c) { return (! isalpha(c)) && (c != ' ');});
        return (p == s.end());
    }
    
private:
    /** num of edges (paths)*/
    int m;
    Adj adjList;
    
    /** check if the node is new*/
    bool nodeExists (const std::string& node)
    {
        return adjList.find (node) != adjList.end();
    }
    
    bool BFS (const std::string& origin, const std::string& destination)
    {
        std::list<std::string> queue {origin};
        std::unordered_map<std::string, bool> visited;
        while (queue.size())
        {
            auto current = queue.front();
            queue.pop_front();
            /** traverse through the list of ePair (nodeId,  weight). */
            for (auto connected : adjList[current])
            {
                /** check for nodeId if it has been already visited. */
                if (visited.count(connected) == 0)
                {
                    if (connected == destination)
                        return true;
                    queue.push_back (connected);
                    visited[connected] = true;
                }
            }
        }
        return false;
    }
};

#endif /* PathGraph_h */

