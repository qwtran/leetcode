/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

const int mapSize = 100;

struct Index {
    int index;
    struct Index* nextIndex;
}

struct Node {
    int value;
    struct Index* indexList;
    struct Node* nextNode;
};

struct Node** nodeMap;

void initMap() {
    nodeMap = (struct Node**) calloc(mapSize, sizeof(struct Node*));
}

void put(int index, int value) {
    struct Index* indexStruct = (struct Index*) malloc(sizeof(struct Index));
    indexStruct->index = index;
    indexStruct->nextIndex = 0;

    struct Node* entryNode = (struct Node*) malloc(sizeof(struct Node));
    entryNode->value = i;
    entryNode->nextNode = 0;

    struct Node* indexNode = nodeMap[i % mapSize];

    if(indexNode == 0) {
        nodeMap[i % mapSize] = entryNode;
        entryNode->indexList = indexStruct;
        return;
    }

    while(indexNode != 0) {
        if(indexNode->value == value) {
            struct Index* temp = indexNode->indexList;
            while(temp != 0) {
                if(temp->nextIndex == 0) {
                    temp->nextIndex = indexStruct;
                    return;
                }
                temp = temp->nextIndex;
            }
            return;
        }
        if(indexNode->nextNode == 0) {
            indexNode->nextNode = entryNode;
            entryNode->indexList = indexStruct;
            return;
        } else {
            indexNode = indexNode->nextNode;
        }
    }
    assert(false);
}

int contains(int i) {
    int count = 0;
    struct Node* indexNode = nodeMap[i % mapSize];
    while(indexNode != 0) {
        if(indexNode->value == i) {
            ++count;
        }
        indexNode = indexNode->nextNode;
    }
    return count;
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
    initMap();
    
    # fill map
    for(int i = 0; i < numsSize; ++i) {
        put(nums[i]);
        if(contains(target - nums[i])) {
            //cleanUp();
            return malloc(2*sizeof(int));
        }
    }
    assert(false);
}
