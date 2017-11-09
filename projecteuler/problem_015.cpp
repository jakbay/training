#include <iostream>
#include <tuple>
#include <vector>
#include <thread>
#include <mutex>

class Node
{
	public:
		Node() : m_next1(nullptr), m_next2(nullptr)
		{

		}

		void init(Node *next1, Node *next2)
		{
			if (next1) {
				m_next1 = next1;
			}
			if (next2) {
				m_next2 = next2;
			}
		}

		std::tuple<Node *, Node *> getNext()
		{
			return std::make_tuple(m_next1, m_next2);
		}

	private:
		Node *m_next1;
		Node *m_next2;
};

class Table
{
	public:
		Table(uint64_t w, uint64_t l) : m_w(w + 1), m_h(l + 1), m_paths(0), m_jobs(0)
		{
			init();
		}

		~Table()
		{
			for (auto i = 0; i < m_w; ++i) {
				for (auto j = 0; j < m_h; ++j) {
					delete m_nodes[i][j];
				}
			}
		}

		uint64_t countPaths()
		{
			m_paths = 0;
			if (!m_nodes.size() || !m_nodes[0].size()) {
				return m_paths;
			}
			nodeGrabber(this, m_nodes[0][0]);
			return m_paths;	
		}

	private:
		static void nodeGrabber(Table *t, Node *n)
		{
			std::tuple<Node *, Node *> &&tmp = n->getNext();
			Node *n1 = std::get<0>(tmp);
			Node *n2 = std::get<1>(tmp);
			int64_t jobsAvailable = 0;
			std::thread job1;
			std::thread job2;
			t->m_sync.lock();
			jobsAvailable = 7 - t->m_jobs;
			t->m_sync.unlock();
			if (n1) {
				if (jobsAvailable > 0) {
					job1 = std::thread(nodeGrabber, t, n1);	
					t->m_sync.lock();
					++t->m_jobs;
					--jobsAvailable;
					t->m_sync.unlock();
				} else {
					nodeGrabber(t, n1);
				}
			}
			if (n2) {
				if (jobsAvailable > 0) {
					job2 = std::thread(nodeGrabber, t, n2);	
					t->m_sync.lock();
					++t->m_jobs;
					--jobsAvailable;
					t->m_sync.unlock();
				} else {
					nodeGrabber(t, n2);
				}
			}
			if (job1.joinable()) {
				job1.join();
				t->m_sync.lock();
				--t->m_jobs;
				t->m_sync.unlock();
			}
			if (job2.joinable()) {
				job2.join();
				t->m_sync.lock();
				--t->m_jobs;
				t->m_sync.unlock();
			}
			if (!n1 && !n2) {
				t->m_sync.lock();
				++t->m_paths;
				t->m_sync.unlock();
			}
		}

		void init() {
			if (!m_w || !m_h) {
				return;
			}
			for (auto i = 0; i < m_w; ++i) {
				std::vector<Node *> &&v = std::vector<Node *>();
				for (auto j = 0; j < m_h; ++j) {
					v.push_back(new Node());
				}
				m_nodes.push_back(v);
			}
			for (auto i = 0; i < m_h - 1; ++i) {
				for (auto j = 0; j < m_w - 1; ++j) {
					m_nodes[i][j]->init(m_nodes[i + 1][j], m_nodes[i][j + 1]);
				}
				m_nodes[i][m_h - 1]->init(nullptr, m_nodes[i + 1][m_w - 1]);
			}
			for (auto j = 0; j < m_w - 1; ++j) {
				m_nodes[m_h - 1][j]->init(m_nodes[m_h - 1][j + 1], nullptr);
			}
			m_nodes[m_w - 1][m_h - 1]->init(nullptr, nullptr);
		}

		uint64_t m_w;
		uint64_t m_h;
		uint64_t m_paths;
		std::vector<std::vector<Node *>> m_nodes;
		std::mutex m_sync;
		uint64_t m_jobs;
};


int main()
{
	Table t(20, 20);
	std::cout << "The result is: " << t.countPaths() << std::endl;
	return 0;
}
