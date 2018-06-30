#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
using namespace std;

//defining the indexes of nodes of graph as name of buildings for ease
#define GDN 0
#define MB 1
#define SMV 2
#define TT 3
#define SJT 4
#define MBlock 5
#define PBlock 6
#define NBlock 7

//this edge between two nodes is defined by this structure
struct edge
{
    int neighbour,distance;
};

vector<vector<edge> > adjList(8); // a 2d vector for storing the nodes and their neighbor
vector<int> visited(8,0);
vector<int> shortestDistance(8,INT_MAX);
vector<int> maxDistances(8);

// function to form the map of VIT as a graph data structure
void formGraph()
{
    edge e;
    // doing for GDN
    e.neighbour = MB;
    e.distance = 180;
    adjList[GDN].push_back(e);
    // doing for MB
    e.neighbour = GDN;
    e.distance = 180;
    adjList[MB].push_back(e);
    e.neighbour = SMV;
    e.distance = 180;
    adjList[MB].push_back(e);
    //doing fOr SMV
    e.neighbour = MB;
    e.distance = 180;
    adjList[SMV].push_back(e);
    e.neighbour = TT;
    e.distance = 350;
    adjList[SMV].push_back(e);
    //doing for TT
    e.neighbour = SMV;
    e.distance = 350;
    adjList[TT].push_back(e);
    e.neighbour = SJT;
    e.distance = 550;
    adjList[TT].push_back(e);
    e.neighbour = MBlock;
    e.distance = 750;
    adjList[TT].push_back(e);
    //doing for SJT
    e.neighbour = TT;
    e.distance = 550;
    adjList[SJT].push_back(e);
    //doing for M
    e.neighbour = TT;
    e.distance = 750;
    adjList[MBlock].push_back(e);
    e.neighbour = PBlock;
    e.distance = 230;
    adjList[MBlock].push_back(e);
    //doing for P
    e.neighbour = MBlock;
    e.distance = 230;
    adjList[PBlock].push_back(e);
    e.neighbour = NBlock;
    e.distance = 120;
    adjList[PBlock].push_back(e);
    //doing for N
    e.neighbour = PBlock;
    e.distance = 120;
    adjList[NBlock].push_back(e);
}

// sorting is required for the proper functioning of Dijkstra's Algorithm as it needs the neighbor with least distance at each iteration
void sortAdjList()
{
   for(int i = 0; i < 8; i++)
    {
        for(unsigned int j = 0; j < adjList[i].size();j++)
        {
            for(unsigned int k = j + 1; k < adjList[i].size();k++)
            {
                if(adjList[i][j].distance > adjList[i][k].distance)
                {
                    edge temp;
                    temp.distance = adjList[i][j].distance;
                    temp.neighbour = adjList[i][j].neighbour;
                    adjList[i][j].distance = adjList[i][k].distance;
                    adjList[i][j].neighbour = adjList[i][k].neighbour;
                    adjList[i][k].distance = temp.distance;
                    adjList[i][k].neighbour = temp.neighbour;
                }
            }
        }
    }
}

//function for Dijkstra's algorithm, parameter passed is the node for which the algorithm is to be applied.
// after completion, the vector shortestDistance will have the shortest distance from ith node to each node
void dijkstra(int i)
{
    visited[i] = 1;
    for(unsigned int j = 0; j < adjList[i].size(); j++)
    {
        if(!visited[adjList[i][j].neighbour])
        {
            if(adjList[i][j].distance + shortestDistance[i] < shortestDistance[adjList[i][j].neighbour])
                shortestDistance[adjList[i][j].neighbour] = adjList[i][j].distance + shortestDistance[i];
            dijkstra(adjList[i][j].neighbour);
        }
    }
}

//this initializes the shortestDistance and visited vector for application of Dijkstra's
void initialize(int n, int j)
{
    for(int i = 0; i < n; i ++)
    {
        shortestDistance[i] = INT_MAX;
        visited[i] = 0;
    }
    shortestDistance[j] = 0;
}

//finds the maximum value from shortestDistance vector
int maxShortestDistance()
{
    int max_elementt = 0;
    for(unsigned int i=0; i < shortestDistance.size(); i++)
    {
        if(max_elementt < shortestDistance[i])
            max_elementt = shortestDistance[i];
    }
    return max_elementt;
}

//this finds the index of the minimum value from maxDistances vector which would be the meeting point
int findMeetingPoint()
{
    int mn = maxDistances[0],meetingPoint = 0;
    for(int i = 1; i < 8; i++)
    {
        if(maxDistances[i] < mn)
        {
            mn = maxDistances[i];
            meetingPoint = i;
        }
    }
    return meetingPoint;
}

void displayAdjList()
{
    for(int i = 0; i < 8; i++)
    {
        for(unsigned int j = 0; j < adjList[i].size();j++)
            cout<<adjList[i][j].neighbour<<" "<<adjList[i][j].distance<<" -- ";
        cout<<endl;
    }
}

int main()
{
    formGraph();
    sortAdjList();

    // applying Dijkstra's algorithm for each node of the graph and then finding the maximum value of the shortest distances
    for(int i = 0; i < 8; i++)
    {
        initialize(8,i);
        dijkstra(i);
        maxDistances[i] = maxShortestDistance();
    }

    int meetingPoint = findMeetingPoint();
    switch(meetingPoint)
    {
        case 0 : cout<<"GDN";break;
        case 1 : cout<<"MB";break;
        case 2 : cout<<"SMV";break;
        case 3 : cout<<"TT";break;
        case 4 : cout<<"SJT";break;
        case 5 : cout<<"M Block";break;
        case 6 : cout<<"P Block";break;
        case 7 : cout<<"N Block";break;
    }
    cout<<endl;

    return 0;
}
