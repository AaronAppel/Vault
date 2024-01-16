/*
    Legal: BSD-3 Clause
    Author: Aaron Appel
    Date: May 2nd 2018
    Purpose: To solve this the tower hopper problem as reviewed in this video: https://www.youtube.com/watch?v=kHWy5nEfRIQ
             I also used this opportunity to learn graph creation and traversing.
*/

#include <time.h>
#include <vector>
#include <stack>
#include <cassert>
#include <iostream>

const float END_NODE_VALUE = -1.0f; // -1.0f to represent an end node
const float NULL_NODE_VALUE = -2.0f; // null (-2.0f) to start since towers can't be negative

struct GraphNode
{
    GraphNode() {};
    GraphNode(float value) { m_Value = value; }
    ~GraphNode() {}

    float m_Value = NULL_NODE_VALUE;
    std::vector<GraphNode*> m_Links;
    bool m_Open = true;
};

const int* GenerateTowerData(int numTowers, int maxHeight);
GraphNode* GenerateTowerGraphUsingArray(const int nodes[], const int size);
bool GraphIsHoppable(GraphNode* headNode);

int main()
{
	const int maxTowers = 20;
	const int maxTowerHeight = 5;
    const int* towerData = nullptr;
    char userChoice = 0;
	int currentNumTowers = 0;
	GraphNode* headNode = nullptr;

    srand(NULL); // seed RNG

    do
    {
        std::cout << "Hello\n";
		std::cout << "1)Generate towers\n";
		std::cout << "2)print towers\n";
		std::cout << "3)Solve towers\n";
		std::cout << "4)Clear screen\n";
		std::cout << "0)Quit\n";

        std::cin >> userChoice;

        switch (userChoice)
        {
		// case '0': quit
		case '1':
			if (towerData != nullptr)
				delete towerData;
			if (headNode != nullptr)
				delete[] headNode;

			currentNumTowers = rand() % maxTowers + 1;
			towerData = GenerateTowerData(currentNumTowers, maxTowerHeight);

			headNode = GenerateTowerGraphUsingArray(towerData, currentNumTowers);
			break;
		case '2':
			std::cout << "Towers:";
			for (int i = 0; i < currentNumTowers; i++)
			{
				std::cout << " " << towerData[i];
			}
			std::cout << "\n" << std::endl;
			break;
		case '3':
			std::cout << "Result: " << GraphIsHoppable(headNode) << std::endl;
			break;
		case '4':
			system("CLS");
			break;
        }
    } while (userChoice != '0');

	// clean up
	if (towerData != nullptr)
		delete towerData;

    if (headNode != nullptr)
        delete[] headNode;
}

const int* GenerateTowerData(int numTowers, int maxHeight)
{
    int* retValue = new int[numTowers];

    for (int i = 0; i < numTowers; i++)
    {
		retValue[i] = rand() % maxHeight;
    }

    return retValue;
}

bool GraphIsHoppable(GraphNode* headNode)
{
    assert(headNode != nullptr);

    // traverse graph looking for solution
    std::stack<GraphNode*> trail; // list of current nodes in path
    trail.push(headNode);

    bool isHoppable = false; // return value

    while (true)
    {
        // next value
        GraphNode* current = trail.top();

        if (current->m_Value == END_NODE_VALUE) // end?
        {
            isHoppable = true; // solved
            std::cout << "\nSolved Trail:\n";
            int size = trail.size();
            for (int i = 0; i < size; i++)
            {
                std::cout << trail.top()->m_Value << ", ";
                trail.pop();
            }
            std::cout << std::endl;
            break; // breakout of while
        }

        if (current->m_Links.size() == 0) // no links
        {
            current->m_Open = false; // not viable
            trail.pop();

            if (trail.size() == 0)
            {
                isHoppable = false; // no solution
                break; // breakout of while
            }
        }
        else
        {
            // Note: searching from back to front often saves several steps, but it is less intuitive for debugging.
            // It is more efficient in this case because we can skip values.
            // Note: If we want less steps then we can also compare all links and push back the largest open node each time.
            // This would effectively skip more nodes that maybe be redundant.
            for (int i = current->m_Links.size() - 1; i > -1; i--)
            {
                if (current->m_Links[i]->m_Open == true)
                {
                    trail.push(current->m_Links[i]); // add new node to check
                    break; // don't add more nodes yet
                }
            }

            if (current == trail.top()) // new node on top of stack?
            {
                // all nodes closed
                current->m_Open = false;
                trail.pop();
                if (trail.size() == 0)
                {
                    isHoppable = false; // no solution
                    break; // breakout of while
                }
            }
        }
    }

    return isHoppable;
}

GraphNode* GenerateTowerGraphUsingArray(const int nodes[], const int size)
{
    // create list of nodes
    GraphNode* nodesList = new GraphNode[size + 1]; // 1 extra end node

    // assign values
    for (int i = 0; i < size; i++)
    {
        nodesList[i].m_Value = nodes[i];
    }
    nodesList[size].m_Value = END_NODE_VALUE; // mark as end node

    // genereate the graph by linking nodes
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < nodesList[i].m_Value; j++)
        {
            int index = i + 1 + j; // i (current index or me) + 1 (move over 1) + j (current linked node)
            if (index < size) // inside array?
            {
                nodesList[i].m_Links.push_back(&nodesList[index]); // add link to node
            }
            else
            {
                // this node can hop to the end. add end of array node
                nodesList[i].m_Links.push_back(&nodesList[size]);
                break; // prevent additional links to the end
            }
        }
    }

    // remember to delete nodes
    return nodesList;
}