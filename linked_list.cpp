#include "linked_list.hpp"

// Constructor
ListD::ListD()
{
  head = nullptr;
  tail = nullptr;
  length = 0;
}

// Destructor
ListD::~ListD()
{
  doubleNode* cur = head;
  while (cur != nullptr)
  {
    doubleNode* nextNode = cur->next;
    delete cur;
    cur = nextNode;
  }
}

// Check if the list is empty
bool ListD::IsEmpty() const
{
  return head == nullptr;
}

// Insert a new node into the doubly linked list 
void ListD::Insert(int street_id, int block_id, int treeNum, int NorthDistance, int SouthDistance)
{
  doubleNode* tmp = new doubleNode(street_id, block_id, treeNum, NorthDistance, SouthDistance);

  if (length == 0)  // List is empty
  {
    head = tail = tmp;
  }
  else  // Insert at the end
  {
    tail->next = tmp;
    tmp->prev = tail;
    tail = tmp;
  }
  length++;
}

// Search for a node by street_id and block_id
doubleNode* ListD::Search(const int street_id, const int block_id) const
{
  doubleNode* cur = head;  
  while (cur != nullptr)  
  {
    if (cur->street_id == street_id && cur->block_id == block_id)
    {
      return cur; 
    }
    cur = cur->next;
  }
  return nullptr;
}

// Print the node's details based on street_id and block_id
void ListD::Print(int street_id, int block_id) const
{
  doubleNode* foundNode = Search(street_id, block_id);

  if (foundNode != nullptr)
  {
    cout << "Tree Number: " << foundNode->treeNum 
         << ", North distance of the block: " << foundNode->NorthDistance << " ft" 
         << ", South distance of the block: " << foundNode->SouthDistance << " ft\n";
  }
  else  // If no matching node was found
  {
    cout << "No trees found for street ID " << street_id << " and block ID " << block_id << ".\n";
  }
}

// Delete a node at the given position
void ListD::Delete(int street_id)
{
  if (head == nullptr)
  {
    cout << "List is empty.\n";
    return;
  }
  
  doubleNode* cur = head;
  
  // Case: deleting the head node
  if (cur->street_id == street_id) 
  {
    head = cur->next;
    if (head != nullptr) {
      head->prev = nullptr;
      } else {
      tail = nullptr;  // If head becomes nullptr, the list is empty
      }
    delete cur;
    cout << endl;
    return;
  }
  
  // Traverse to find the node to delete
  while (cur != nullptr && cur->street_id != street_id) 
  {
    cur = cur->next;
  }
  
  // Node not found
  if (cur == nullptr) {
    cout << "Street ID not found." << endl;
    return;
  }
  
  // Case: deleting a node in the middle or end
  cur->prev->next = cur->next;
  if (cur->next != nullptr) 
  {
    cur->next->prev = cur->prev;
    } else {
    // Deleting the tail node
    tail = cur->prev;
    }
  delete cur;
  cout << "Deleted street_id: " << street_id << endl;
}

void ListD::PrintForward()
{
  if (head == nullptr) {
    cout << "List is empty." << endl;
    return;
  }

  doubleNode* temp = head;
  while (temp != nullptr) {
    cout << "Street: " << temp->street_id 
         << ", Block: " << temp->block_id
         << ", Tree #: " << temp->treeNum
         << ", North Distance: " << temp->NorthDistance
         << ", South Distance: " << temp->SouthDistance
         << endl;
    temp = temp->next;
  }
}

// Function to read the file and insert data into the doubly linked list
void readFile(const string& fileName, ListD& list)
{
  ifstream file(fileName);
  if (!file.is_open())
  {
    cout << "Unable to open file" << endl;
    return;
  }
  
  string line;
  while (getline(file, line))// read each line of the file
  {
    int street_id, block_id, treeNum, NorthDistance, SouthDistance;
    istringstream iss(line);// create a string stream from the line
    if (iss >> street_id >> block_id >> treeNum >> NorthDistance >> SouthDistance) // Extract data from the line
    {
      list.Insert(street_id, block_id, treeNum, NorthDistance, SouthDistance);
    }
  }
  file.close();
}

void menu()
{
  cout << "Welcome to the Logan neighborhood!" << endl;
  cout << "Please select the street and block you want to check." << endl;
  cout << "Navigation will be from East to West." << endl;
  cout << "|--------------------------------------------| " << endl;
  cout << "|     street id:     |        block id:      |" << endl;
  cout << "|--------------------+-----------------------|" << endl;
  cout << "|E Indian Ave: 1     | 1, 2, 3, 4, 5, 6, 7   |" << endl;
  cout << "|--------------------+-----------------------|" << endl;
  cout << "|E Nora Ave: 2       | 1, 2, 3, 4, 5, 6, 7   |" << endl;
  cout << "|--------------------+-----------------------|" << endl;
  cout << "|E Augusta Ave: 3    | 1, 2, 3, 4, 5, 6      |" << endl;
  cout << "|--------------------------------------------|" << endl;
  cout << "|Mission Ave: 4      | 1, 2, 3, 4, 5, 6, 7   |" << endl;
  cout << "|--------------------------------------------|" << endl;
  cout << "|E Sinto Ave: 5      | 1, 2, 3, 4, 5, 6, 7, 8|" << endl;
  cout << "|--------------------------------------------|" << endl;
  cout << "|E Sharp Ave: 6      | 1, 2, 3, 4, 5, 6, 7, 8|" << endl;
  cout << "|--------------------------------------------|" << endl;
}