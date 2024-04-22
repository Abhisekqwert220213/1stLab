#include <stdio.h>

int flag[500]={0}; // Array to mark the number of times each node is traversed
int x=0; // Counter to count the number of paths from the start node to the end node
int y=0; // Start node
int z=0; // End node

struct Node
{
    int nodeid; // Node ID
    int adjcount; // Number of adjacent nodes
    int adjs[10]; // Array to store adjacent nodes
    int costs[10]; // Array to store the cost of reaching adjacent nodes
};

// Function to add a new node
int addNode (struct Node * p, int nid, int count)
{
    int i =0, ncount = count;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid) { break; }
    }
    if (i == count)
    {
        p[i].nodeid = nid; // Assign the node ID
        p[i].adjcount = 0; // Initialize the number of adjacent nodes to zero
        ncount++; // Increment the count of nodes
    }
    return ncount; // Return the updated count of nodes
}

// Function to add adjacent nodes
void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i =0, index;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2; // Add the adjacent node
            p[i].costs[c] = cost; // Assign the cost of reaching the adjacent node
            p[i].adjcount = c+1; // Increment the count of adjacent nodes

            break;
        }
    }
}

// Function to check if a node is already added to the list
int added (int * list, int lcount, int nid)
{
    int i =0;
    for (i=0;i<lcount;i++)
    {
        if (list[i] == nid) { return 1; } // If the node is already in the list, return 1
    }
    return 0; // If the node is not in the list, return 0
}

// Recursive function to find all paths between two nodes
void findpath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount)
{
    int index = 0, i=0;

    // Check if the list contains the end node
    if (list[lcount-1] == end)
    {
        x++; // Increment the number of paths found
        int tcost = 0;
        printf ("\n");
        for (i=0;i<lcount;i++)
        {
            flag[list[i]]++; // Mark the node as traversed
            printf (" %d ", list[i]); // Print the node
            tcost += clist[i]; // Calculate the total cost
        }
        printf (" cost = %d", tcost); // Print the total cost
        return;
    }

    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == start) { index = i; break; }
    }

    for (i=0;i<p[index].adjcount;i++)
    {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath (p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main() {
    //printf("Hello world");

    struct Node nodes[50]; // Array to store the nodes
    int nodecount = 0; // Count of the nodes
    int n1=0, n2=0, c = 0;

    // Inputting node connections and costs
    while (1)
    {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9) {break;} // Termination condition
        nodecount = addNode (&nodes[0], n1, nodecount); // Add the first node
        nodecount = addNode (&nodes[0], n2, nodecount); // Add the second node

        addAdjacent (&nodes[0], n1, n2, c, nodecount); // Add the adjacent nodes
        addAdjacent (&nodes[0], n2, n1, c, nodecount); // Add the adjacent nodes
    }

    // Inputting start and end nodes
    int start, end;
    printf ("start, end ? ");
    scanf ("%d %d", &start, &end);
    y=start;
    z=end;
    int list[50], clist[50], lcount = 0; // Arrays to store the list of nodes and their costs
    list[0] = start; clist[0] = 0; lcount = 1;

    // Finding all paths between start and end nodes
    findpath (nodes, nodecount, start, end, list, clist, lcount);

    // Printing essential nodes
    printf("\nEssential nodes :");
    for(int i=0;i<500;i++){
        if(flag[i]==x){
            if(i!=y&&i!=z)
                printf("%d ",i);
        }
    }

    return 0;
}
