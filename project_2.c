#include <stdio.h>

// Structure to represent a node in the graph
struct Node
{
    int nodeid;     // Node ID
    int adjcount;   // Number of adjacent nodes
    int adjs[10];   // Array to store adjacent nodes
    int costs[10];  // Array to store the cost of reaching adjacent nodes
};

// Function to add a new node
int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;
    // Loop to check if the node already exists
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    // If the node does not exist, add it
    if (i == count)
    {
        p[i].nodeid = nid;      // Assign the node ID
        p[i].adjcount = 0;      // Initialize the number of adjacent nodes to zero
        ncount++;               // Increment the count of nodes
    }
    return ncount;  // Return the updated count of nodes
}

// Function to add adjacent nodes
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;
    // Loop to find the node
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;    // Add the adjacent node
            p[i].costs[c] = cost;   // Assign the cost of reaching the adjacent node
            p[i].adjcount = c + 1;  // Increment the count of adjacent nodes
            break;
        }
    }
}

// Function to find all triangles in the graph
void findTriangles(struct Node *p, int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            for (int k = j + 1; k < count; k++)
            {
                int node1 = p[i].nodeid;
                int node2 = p[j].nodeid;
                int node3 = p[k].nodeid;
                int edge1 = 0, edge2 = 0, edge3 = 0;
                // Loop to count the number of edges between the nodes
                for (int x = 0; x < p[i].adjcount; x++)
                {
                    if (p[i].adjs[x] == node2 || p[i].adjs[x] == node3)
                    {
                        edge1++;
                    }
                }
                for (int y = 0; y < p[j].adjcount; y++)
                {
                    if (p[j].adjs[y] == node1 || p[j].adjs[y] == node3)
                    {
                        edge2++;
                    }
                }
                for (int z = 0; z < p[k].adjcount; z++)
                {
                    if (p[k].adjs[z] == node1 || p[k].adjs[z] == node2)
                    {
                        edge3++;
                    }
                }
                // If the number of edges between each pair of nodes is 2, a triangle is formed
                if (edge1 == 2 && edge2 == 2 && edge3 == 2)
                {
                    printf("Triangle found: %d %d %d %d\n", node1, node2, node3, node1);
                }
            }
        }
    }
}

int main()
{
    struct Node nodes[50];  // Array to store the nodes
    int nodecount = 0;      // Count of the nodes
    int n1 = 0, n2 = 0, c = 0;

    // Inputting node connections and costs
    while (1)
    {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        // Termination condition
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break;
        }
        // Add the first node
        nodecount = addNode(&nodes[0], n1, nodecount);
        // Add the second node
        nodecount = addNode(&nodes[0], n2, nodecount);

        // Add the adjacent nodes
        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    // Finding all triangles in the graph
    findTriangles(nodes, nodecount);

    return 0;
}
