#include <stdlib.h>
#include <stdio.h>


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

const int mapSize = 100;

struct Index {
    // for any value, there can be duplicates. track all indexes with this list.
    int index;
    struct Index* nextIndex;
};

struct Node {
    // node contains a value and a list of index associated with the value
    int value;
    struct Index* indexList;
    struct Node* nextNode;
};

struct Node** nodeMap;

void initMap() {
    nodeMap = (struct Node**) calloc(mapSize, sizeof(struct Node*));
}

void put(int index, int value) {
    // create new index struct for this value
    struct Index* indexStruct = (struct Index*) malloc(sizeof(struct Index));
    indexStruct->index = index;
    indexStruct->nextIndex = 0;

    // create new node for this value
    struct Node* entryNode = (struct Node*) malloc(sizeof(struct Node));
    entryNode->value = value;
    entryNode->nextNode = 0;

    // get node ptr for this value
    struct Node* indexNode = nodeMap[abs(value) % mapSize];

    // node ptr points to null, value has not been added, so create node
    if(indexNode == 0) {
        nodeMap[abs(value) % mapSize] = entryNode;
        entryNode->indexList = indexStruct;
        return;
    }

    // node exists, find node with correct value, else create add new node
    while(indexNode != 0) {
        if(indexNode->value == value) {
            // node for value found, append this index to end of index list
            struct Index* temp = indexNode->indexList;
            while(temp != 0) {
                if(temp->nextIndex == 0) {
                    temp->nextIndex = indexStruct;
                    return;
                }
                temp = temp->nextIndex;
            }
        }

        if(indexNode->nextNode == 0) {
            // reached the end, node with this value does not exist, so append this node to end
            indexNode->nextNode = entryNode;
            entryNode->indexList = indexStruct;
            return;
        }
        
        indexNode = indexNode->nextNode;
    }
}

struct Index* contains(int i) {
    struct Node* indexNode = nodeMap[abs(i) % mapSize];
    while(indexNode != 0) {
        if(indexNode->value == i) {
            return indexNode->indexList;
        }
        indexNode = indexNode->nextNode;
    }
    return 0;
}

void cleanUp() {
    struct Node* indexNode = 0;
    struct Node* nextNode = 0;
    for(int i = 0; i < mapSize; ++i) {
        struct Node* indexNode = nodeMap[i];
        while(indexNode != 0) {
            if(indexNode->nextNode != 0) {
                nextNode = indexNode->nextNode;
                free(indexNode);
                indexNode = nextNode;
            } else {
                free(indexNode);
            }
        }
    }
}

int* twoSum(int* nums, int numsSize, int target) {
    // init map
    initMap();
    
    // fill map
    for(int i = 0; i < numsSize; ++i) {
        put(i, nums[i]);

	struct Index* indexResults = contains(target - nums[i]);
        if(indexResults) {
            if(indexResults->index != i) {
                int* result = (int*) malloc(2*sizeof(int));
		result[0] = i;
		result[1] = indexResults->index;
		//cleanUp();
		return result;
            }
            indexResults = indexResults->nextIndex;
        }
    }
    return 0;
}


int main() {
    int nums[] = {1, 3, 5, -10, 1};
    int* results = twoSum(nums, sizeof(nums)/sizeof(int), 2);
    if(results)
        printf("%i %i\n", results[0], results[1]);
    else
        printf("None\n");
    return 0;
}

