#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <exception>

using std::vector;
using std::string;

class StrBlob {
public:
	friend class StrBlobPtr;
	using size_type=vector<string>::size_type;
	StrBlobPtr begin();
	StrBlobPtr end();
	StrBlob() :data(std::make_shared<vector<string>>()) {}
	StrBlob(std::initializer_list<string> il) :data(std::make_shared<vector<string>>(il)) {}
	size_type size() const {
		return data->size();  
	}
	bool empty() const {          //make_shared()���ص���һ��ָ�룬ָ��vector<string> 
		return data->empty();     //����data-> �ǽ�����ָ�룬�õ�һ��vector<string>
 	}                             //Ȼ����������ĳ�Ա����push_back������size(),empty()
	void push_back(const string& t) {
		data->push_back(t);
	}
	void pop_back() {                   //����֮ǰ�ȼ�������Ƿ��ںϷ���Χ��
		check(0, "pop_back on empty StrBlob");
		return data->pop_back();
	}
	string& front() {
		check(0, "front on empty StrBlob");
		return data->front();
	}
	string& back() {
		check(0, "back on empty StrBlon");
		return data->back();
	}
	//���ذ汾
	const string& front() const {
		check(0, "front on empty StrBlob");
		return data->front();
	}
	const string& back() const {
		check(0, "back on empty StrBlob");
		return data->back();
	}

private:
	std::shared_ptr<vector<string>> data;  //data��һ������ָ�룬ָ��ײ�vector
	void check(size_type i, const string& msg) const {
		if (i >= data->size()) //������ָ�벢����size������������ʵ���ǻ��vector��Ԫ�ص���Ŀ
			throw std::out_of_range(msg);
	}
};
class StrBlobPtr {
private:
	std::weak_ptr<vector<string>> wptr;
	std::size_t curr;
	std::shared_ptr<vector<string>> check(std::size_t, const string&) const;
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) :wptr(a.data), curr(sz) {} //Ĭ������½�curr��ʼ��Ϊ��һ��Ԫ�ص��±�
	string& deref() const;
	StrBlobPtr& incr();
	bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
}; 
std::shared_ptr<vector<string>> StrBlobPtr::check(std::size_t i, const string &msg) const {
	auto ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBlobStr");
	if (i >= ret->size())  //������ָ�벢����size������������ʵ���ǻ��vector��Ԫ�ص���Ŀ
		throw std::out_of_range(msg);  //����
	return ret;  //��vector�����ڣ�����ָ��vector������ָ��
}
string& StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr]; //�˴�����ʹ��p->����Ϊ�±���Ҫ�����Ա��������ᱨ��.
}
StrBlobPtr& StrBlobPtr::incr() {
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}
StrBlobPtr StrBlob::begin() {               /*Ϊʲô�Ұ�begin������end����������StrBlob֮�ھͻᱨ��ʹ��δ����������ͣ�*/
	return StrBlobPtr(*this); //
}
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}