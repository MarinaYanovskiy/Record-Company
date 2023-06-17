#include "UnionFind.h"
UnionFind::UnionFind()
    : m_numOfRecords(0), m_records(nullptr), m_recordsMappedToGroups(nullptr) {}

UnionFind::~UnionFind() {
  for (int i = 0; i < m_numOfRecords; i++) {
    delete m_recordsMappedToGroups[i];
  }
  if (m_numOfRecords > 0) {
    delete[] m_recordsMappedToGroups;
    delete[] m_records;
    //   m_groups.deleteList();
  }
}

void UnionFind::reset(int *record_stocks, int number_of_records) {
  for (int i = 0; i < m_numOfRecords; i++) {
    delete m_recordsMappedToGroups[i];
  }

  delete[] m_recordsMappedToGroups;
  delete[] m_records;

  if (m_numOfRecords > 0) {
    m_groups.deleteList();
  }

  m_recordsMappedToGroups = new nodeInGroup *[number_of_records];
  m_records = new CDRecord[number_of_records];
  m_numOfRecords = number_of_records;
  for (int i = 0; i < number_of_records; i++) {
    m_records[i] = CDRecord(i, record_stocks[i]);
    m_recordsMappedToGroups[i] = MakeSet(m_records[i]);
  }
}

nodeInGroup *UnionFind::MakeSet(CDRecord record) {
  nodeInGroup *node = new nodeInGroup(record);
  Group *group = new Group(record.getColumns(), record.getCopies(), 1, node);
  m_groups.insert(group);
  node->setGroup(group);
  return node;
}

Group *UnionFind::Find(int record) const {
  nodeInGroup *temp2, *temp1 = m_recordsMappedToGroups[record],
                      *root = m_recordsMappedToGroups[record];
  int total_path_sum = 0, sum_to_substract = 0, current_extra = 0;
  while (root->getFather()) {
    total_path_sum += root->getExtraHight();
    root = root->getFather();
  }

  // shrink paths to root
  while ((temp1->getFather()) && (temp1->getFather() != root)) {
    temp2 = temp1;
    temp1 = temp1->getFather();
    temp2->setFather(root);
    current_extra = temp2->getExtraHight();
    temp2->setExtra(total_path_sum - sum_to_substract);
    sum_to_substract += current_extra;
  }
  return root->getGroup();
}

int UnionFind::getColumn(int record) const {
  Group *group = Find(record);
  return group->getColumn();
}

int UnionFind::getHight(int record) const {
  nodeInGroup *node = m_recordsMappedToGroups[record];
  int hight = 0;
  while (node->getFather()) {
    hight += node->getExtraHight();
    node = node->getFather();
  }
  hight += node->getExtraHight();
  return hight;
}

Group *UnionFind::Union(Group *source, Group *destination) {
  if (destination->merge(source) != nullptr) {
    m_groups.remove(source);
    return destination;
  }
  return nullptr;
}

CDRecord *UnionFind::getRecordInPlace(int n) const {
  if (n >= m_numOfRecords) {
    return nullptr;
  }

  return &m_records[n];
}
