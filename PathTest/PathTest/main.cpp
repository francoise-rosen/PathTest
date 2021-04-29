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
        for (auto n : subgraphOne)
            pg.addNode (n);
        for (auto p : subgraphTwo)
            pg.addNode (p);
        /** Subgraph One - A,B,C,D,E are reachable */
        pg.addEdge ("A", "B");
        pg.addEdge ("A", "C");
        pg.addEdge ("A", "D");
        pg.addEdge ("D", "E");
        pg.addEdge ("G", "F");
        
        /** Subgraph Two - F, G, H, I, J are reachable */
        pg.addEdge ("F", "G");
        pg.addEdge ("G", "H");
        pg.addEdge ("H", "I");
        pg.addEdge ("I", "J");
    }
    void TearDown() override
    {
       // pg.clear();
    }
    PathGraph pg;
    static const std::list<std::string> subgraphOne;
    static const std::list<std::string> subgraphTwo;
};

const std::list<std::string> PathClientTest::subgraphOne = {"A","B","C","D","E"};
const std::list<std::string> PathClientTest::subgraphTwo = {"F", "G", "H", "I", "J"};

/** Test if the input is valid (only alpha chars and white space allowed. */
TEST_F (PathClientTest, ValidNameTest)
{
    EXPECT_TRUE (pg.isArgumentValid ("Athens")); // regular
    EXPECT_TRUE (pg.isArgumentValid ("G"));      // one letter
    EXPECT_TRUE (pg.isArgumentValid("Muenchenbladbach"));
    EXPECT_TRUE (pg.isArgumentValid ("Second Bad Vilbel")); // w/ white space
}

/** Test if the input is invalid (only alpha chars and white space allowed. */
TEST_F (PathClientTest, InvalidNameTest)
{
    EXPECT_FALSE (pg.isArgumentValid ("Second; Bad Vilbel2")); // non-alpha
    /** empty string */
    EXPECT_FALSE (pg.isArgumentValid (""));
    /** this must throw since "G:" is an illegal entry. */
    EXPECT_THROW (pg.findPath("A", "G:"), IllegalArgument);
    /** this must throw since "G:" is an illegal entry. */
}

/** Test if path beween two Nodes is not available. */
TEST_F (PathClientTest, PathNotAvailableTest)
{
    /** two subgraphs are disconnected, so any node from the second graph is unreachable from
     any node of the first */
    for (auto it = subgraphOne.begin(); it != subgraphOne.end(); ++it)
    {
        for (auto jt = subgraphTwo.begin(); jt != subgraphTwo.end(); ++jt)
        {
            EXPECT_THROW (pg.findPath(*it, *jt), PathNotFound);
        }
    }
}

TEST_F (PathClientTest, PathAvailableTest)
{
    /** SubgraphOne. If every Node is reachable from the node A, then there's at least one path between all of them*/
    for (auto it = subgraphOne.begin(); it != subgraphOne.end(); ++it)
    {
        EXPECT_NO_THROW (pg.findPath ("A", *it));
    }
}

TEST_F (PathClientTest, ConnectSubgraphTest)
{
    /** connect A with J. Now both subgraphs will connect*/
    pg.addEdge (subgraphOne.front(), subgraphTwo.back());
    
    for (auto it = subgraphOne.begin(); it != subgraphOne.end(); ++it)
    {
        for (auto jt = subgraphTwo.begin(); jt != subgraphTwo.end(); ++jt)
        {
            /** every Node from SubgraphTwo is now reachable from every Node from SubgraphOne*/
            EXPECT_NO_THROW (pg.findPath(*it, *jt));
        }
    }
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
