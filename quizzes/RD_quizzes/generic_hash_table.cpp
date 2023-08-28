#include <iostream>		// cout
#include <vector>		// vector
#include <list>			// list

const char *g_default = "\033[0m";
const char *g_red = "\033[31m";
const char *g_green = "\033[32m";


template <typename K, typename V, typename H = std::hash<K>>
class Hashtable
{
public:
	Hashtable() = default;
	Hashtable(const Hashtable& other) = delete;
	Hashtable& operator=(const Hashtable& other) = delete;
	~Hashtable() = default;

	void Insert(K key, V val);
	V Find(K key);
	void Remove(K key);
	std::size_t Size();

private:
	std::vector<std::list<std::pair<K,V>>> m_table;
	H m_hash;
	void EnlargeVector(int index);
};

template <typename K, typename V, typename H>
void Hashtable<K, V, H>::Insert(K key, V val)
{
	auto bucket = m_hash(key);
	EnlargeVector(bucket);
	for (auto &pair : m_table[bucket])
	{
		if (key == pair.first)
		{
			throw std::runtime_error("Key already exists in hashtable");
		}
	}
	m_table[bucket].push_back(std::make_pair(key, val));
}

template <typename K, typename V, typename H>
V Hashtable<K, V, H>::Find(K key)
{
	auto bucket = m_hash(key);
	if (m_table.size() >= bucket)
	{
		for (auto &pair : m_table[bucket])
		{
			if (key == pair.first)
			{
				return pair.second;
			}
		}
	}
	throw std::out_of_range("Key doesn't exist in hashtable");
}

template <typename K, typename V, typename H>
void Hashtable<K, V, H>::Remove(K key)
{
	auto bucket = m_hash(key);
	if (m_table.size() >= bucket)
	{
		for (auto &pair : m_table[bucket])
		{
			if (key == pair.first)
			{
				m_table[bucket].remove(pair);
				return;
			}
		}
	}
}

template <typename K, typename V, typename H>
std::size_t Hashtable<K, V, H>::Size()
{
	std::size_t counter = 0;

	for (auto &list : m_table)
	{
		counter += list.size();
	}
	return counter;
}

template <typename K, typename V, typename H>
void Hashtable<K, V, H>::EnlargeVector(int index)
{
	int delta = (index - m_table.size()) + 1;
	for (int i = 0; delta > i; ++i)
	{
		m_table.emplace_back();
	}
}

static void PrintTest(size_t test_num, int res, int exp);
static void PrintTest(const char *test_name, size_t test_num, int res, int exp);

int main(void)
{
	Hashtable<std::size_t, std::string> hash;
	std::pair<std::size_t, std::string> data[10] = {std::make_pair(0, "zero"),
												   std::make_pair(1, "one"),
												   std::make_pair(2, "two"),
												   std::make_pair(3, "three"),
												   std::make_pair(4, "four"),
												   std::make_pair(5, "five"),
												   std::make_pair(6, "six"),
												   std::make_pair(7, "seven"),
												   std::make_pair(8, "eight"),
												   std::make_pair(9, "nine")};
	for (std::size_t i = 0; i < 10; ++i)
	{
		hash.Insert(data[i].first, data[i].second);
	}

	for (std::size_t i = 0; i < 10; ++i)
	{
		PrintTest("Find", i + 1, data[i].second == hash.Find(data[i].first), true);
	}

	for (std::size_t i = 0; i < 10; ++i)
	{
		hash.Remove(data[i].first);
		try
		{
			hash.Find(data[i].first);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			std::cerr << g_green << "		Exception caught! - Remove worked!" << g_default << std::endl;
		}
	}

	return 0;
}

/*-------------------------Static Function Definitions------------------------*/
using std::cout;
using std::endl;

static void PrintTest(size_t test_num, int res, int exp)
{
	cout << "Test " << test_num;
	if (exp == res)
	{
		cout << g_green << " SUCCESS";
	}
	else
	{
		cout << g_red << " FAILURE";
	}
	cout << g_default << endl;
}

static void PrintTest(const char *test_name, size_t test_num, int res, int exp)
{
	cout << test_name << " ";
	PrintTest(test_num, res, exp);
}
