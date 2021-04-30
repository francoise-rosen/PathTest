//
//  main.cpp
//  PathTest
//
//  Created by syfo_dias on 29/04/2021.
//

#include <iostream>
#include <gtest/gtest.h>
#include "PathGraph.h"

class PathClientTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        for (auto n : subgraphX)
            pg.addNode (n);
        for (auto p : subgraphY)
            pg.addNode (p);
        /** Subgraph One - A,B,C,D,E are reachable */
        pg.addEdge ("A", "B");
        pg.addEdge ("A", "C");
        pg.addEdge ("A", "D");
        pg.addEdge ("D", "E");
        
        /** Subgraph Two - F, G, H, I, J are reachable */
        pg.addEdge ("F", "G");
        pg.addEdge ("G", "H");
        pg.addEdge ("H", "I");
        pg.addEdge ("I", "J");
        pg.addEdge ("G", "J");
        pg.addEdge ("J", "F");
    }
    void TearDown() override
    {
       // pg.clear();
    }
    PathGraph pg;
    static const std::list<std::string> subgraphX;
    static const std::list<std::string> subgraphY;
};

const std::list<std::string> PathClientTest::subgraphX = {"A", "B", "C", "D", "E"};
const std::list<std::string> PathClientTest::subgraphY = {"F", "G", "H", "I", "J"};

/** Test if the input is valid (only alpha chars and white space allowed. */
TEST_F (PathClientTest, ValidNameTest)
{
    EXPECT_TRUE (pg.isArgumentValid ("G"));      // one letter
    EXPECT_TRUE (pg.isArgumentValid("Muenchenbladbach"));
    EXPECT_TRUE (pg.isArgumentValid ("Second Bad Vilbel")); // w/ white space
    std::string max (163, 'a');
    EXPECT_TRUE (pg.isArgumentValid (max));
}

/** Test if the input is invalid (only alpha chars and white space allowed. */
TEST_F (PathClientTest, InvalidNameTest)
{
    /** non-alpha char */
    EXPECT_FALSE (pg.isArgumentValid ("Second; Bad Vilbel2"));
    /** empty string */
    EXPECT_FALSE (pg.isArgumentValid (""));
}

TEST_F (PathClientTest, IllegalArgumentExceptionTest)
{
    /** this must throw IllegalArgument exeption since "G:" is an illegal entry. */
    EXPECT_THROW (pg.findPath("A", "G:"), IllegalArgument);
    EXPECT_THROW (pg.findPath("G", ""), IllegalArgument);
    std::string outOfRange (164, 'a');
    EXPECT_THROW (pg.findPath(outOfRange, "B"), IllegalArgument);
}

/** Test if path beween two Nodes is not available. */
TEST_F (PathClientTest, PathNotAvailableTest)
{
    /** two subgraphs are disconnected, so any node from the second graph is unreachable from
     any node of the first */
    for (auto it = subgraphX.begin(); it != subgraphX.end(); ++it)
    {
        for (auto jt = subgraphY.begin(); jt != subgraphY.end(); ++jt)
        {
            EXPECT_THROW (pg.findPath(*it, *jt), PathNotFound);
        }
    }
}

/** Test only valid paths. */
TEST_F (PathClientTest, PathAvailableTest)
{
    /** SubgraphX. If every Node is reachable from the node A, then there's at least one path between all of them*/
    for (auto it = subgraphX.begin(); it != subgraphX.end(); ++it)
    {
        EXPECT_NO_THROW (pg.findPath ("A", *it));
    }
    
    /** SubgraphY. If every Node is reachable from the node J, then there's at least one path between all of them*/
    
    for (auto it = subgraphY.begin(); it != subgraphY.end(); ++it)
    {
        EXPECT_NO_THROW (pg.findPath ("J", *it));
    }
}

TEST_F (PathClientTest, ConnectSubgraphTest)
{
    /** connect A with J. Now both subgraphs will connect*/
    pg.addEdge (subgraphX.front(), subgraphY.back());
    
    for (auto it = subgraphX.begin(); it != subgraphX.end(); ++it)
    {
        for (auto jt = subgraphY.begin(); jt != subgraphY.end(); ++jt)
        {
            /** every Node from SubgraphX is now reachable from every Node from SubgraphX*/
            EXPECT_NO_THROW (pg.findPath(*it, *jt));
        }
    }
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
