#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool checkThrough(vector<bool>& visited, const vector<vector<int>>& adjMatrix, int nodeA) {
  
  for (size_t i = 1; i < visited.size(); i++) {
    if (adjMatrix[nodeA][i] == 1) {
      if (visited[i] == true) {
        return true;
      }
      else
        visited[i] = true;
      
      checkThrough(visited, adjMatrix, i);
    }
  }
  
  return false;
}

bool haveSharedAncestor(const vector<vector<int>>& pairs, int nodeA, int nodeB) {
  vector<vector<int>> adjMatrix = vector<vector<int>>(pairs.size()+2, vector<int>(pairs.size()+2, 0));
  
  for (size_t i = 0; i < pairs.size(); i++) {
    adjMatrix[pairs[i][1]][pairs[i][0]] = 1;
  }
  
  vector<bool> ancestorsVisited(pairs.size() + 1, false);
  bool result = false;
  
  checkThrough(ancestorsVisited, adjMatrix, nodeA);
  result = checkThrough(ancestorsVisited, adjMatrix, nodeB);
  
  return result;
}

class Test {
public:
  string name;
  vector<vector<int>> pairs;
  int nodeA;
  int nodeB;
  bool expectedOutput;
};

const vector<Test> tests = {
  {
    // name
    "sample input #1",
    // pairs
    {
      {1, 3},
      {2, 3},
      {3, 6},
      {5, 6},
      {5, 7},
      {4, 5},
      {4, 8},
      {8, 9}
    },
    // nodeA
    3,
    // nodeB
    8,
    // expectedOutput
    false
  }, 
  {
    // name
    "sample input #2",
    // pairs
    {
      {1, 3},
      {2, 3},
      {3, 6},
      {5, 6},
      {5, 7},
      {4, 5},
      {4, 8},
      {8, 9}
    },
    // nodeA
    5,
    // nodeB
    8,
    // expectedOutput
    true
  }
};

bool equalOutputs(bool a, bool b) {
  return a == b;
}

int main() {
  int passed = 0;
  for (auto& test : tests) {
    try {
      auto actualOutput = haveSharedAncestor(test.pairs, test.nodeA, test.nodeB);
      cout << "==> Testing " << test.name << "..." << endl;
      if (equalOutputs(actualOutput, test.expectedOutput)) {
        cout << "PASS" << endl;
        passed++;
      } else {
        cout << "FAIL" << endl;
      }
    } catch (const exception& e) {
      cout << "FAIL" << endl;
      cout << e.what() << endl;
    }
  }
  cout << "==> Passed " << passed << " of " << tests.size() << " tests" << endl;
}
