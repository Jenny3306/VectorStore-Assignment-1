#include "VectorStore.h"

// ArrayList dùng để hiện thực tập hợp các vector
// SLL dùng để hiện thực 1 vector (danh sách các float)

// ----------------- ArrayList Implementation -----------------
// ArrayList có 3 thuộc tính: T* data (mảng động lưu trữ ptu), 
// int capacity (sức chứa tối đa của mảng), int count (số ptu hiện có)
template <class T>
ArrayList<T>::ArrayList(int initCapacity)
{
    // TODO: Khởi tạo mảng rỗng với sức chứa ban đầu initCapacity
    capacity = initCapacity;    // sức chứa ban đầu (theo mặc định là 10)
    count = 0;
    data = nullptr;             // mảng rỗng ban đầu 
    if (capacity > 0) data = new T[capacity];
    // Độ phức tạp: O(1)
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> &other)
{
    // TODO: khởi tạo 1 mảng mới bằng cách sao chép toàn bộ ptu từ danh sách other
    capacity = other.capacity;
    count = other.count;
    data = new T[capacity];
    for (int i = 0; i < count; i++) {
        data[i] = other.data[i];
    }
    // Độ phức tạp: O(n)
}

template <class T>
ArrayList<T>::~ArrayList()
{
    // TODO: Hàm hủy giải phóng toàn bộ vùng nhớ đã cấp phát cho danh sách
    delete[] data;
    data = nullptr;
    count = 0;
    capacity = 0;
    // O(1)
}

// TODO: implement other methods of ArrayList
template <class T>
void ArrayList<T>::ensureCapacity(int cap) {
    // TODO: Đảm bảo mảng có thể chứa ít nhất cap ptu. Nếu cap > capacity => tăng capacity 1.5 lần 
    // và tạo mảng động mới với capacity mới bằng cách sao chép các ptu từ mảng cũ sang mảng mới
    if (cap <= capacity) return;
    int newCap = (capacity > 0 ? capacity : 10);
    while (newCap < cap) {
        long long grown = newCap + (newCap >> 1); // x1.5
        if (grown <= newCap) { // chống tràn
            newCap = cap;
            break;
        }
        newCap = (int)grown;
    }
    T* newData = new T[newCap];
    for (int i = 0; i < count; ++i) newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCap;
    // O(n)
}

template <class T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &other) {
    // TODO: Gán toàn bộ ptu trong danh sách other cho danh sách hiện tại
    if (this != &other) {
        delete[] data; // Free existing resource
        capacity = other.capacity;
        count = other.count;
        data = new T[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }
    return *this; // return the current object (dãy danh sách động)
    // O(n)
}

template <class T>
void ArrayList<T>::add(T e) {
    // TODO: Thêm ptu e vào cuối danh sách, đảm bảo đủ sức chứa
    if (data == nullptr || count >= capacity) {
        ensureCapacity(count + 1); // Ensure capacity is at least 'count + 1' - O(n) in worst case
    }
    data[count++] = e;
    //O(n) in worst case due to ensureCapacity
}

template <class T>
void ArrayList<T>::add(int index, T e) {
    // TODO: Chèn ptu e vào vị trí index, dịch phải các ptu phía sau 1 vị trí
    if (index < 0 || index > count) {
        throw out_of_range("Index is invalid!");
    }
    if (count >= capacity) {
        ensureCapacity(count + 1); // Ensure capacity is at least 'count + 1'
    }
    for (int i = count; i > index; i--) {
        data[i] = data[i - 1];
    }
    data[index] = e;
    count++;
    // O(n)
}

template <class T>
T ArrayList<T>::removeAt(int index){
    // Xóa và trả về ptu tại index, sau đó dịch trái các ptu phía sau 1 vị trí
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    T removedItem = data[index];
    for (int i = index; i < count - 1; i++) {
        data[i] = data[i + 1];
    }
    count--;
    return removedItem; // ở đây removedItem thuộc kiểu dữ liệu T - bất kỳ kiểu dữ liệu gì cx dc
    // O(n)
}

// Ko có hàm xóa ptu đầu tiên có gtri item trong ArrayList

template <class T>
bool ArrayList<T>::empty() const{
    // TODO: Kiểm tra xem danh sách có rỗng không
    return count == 0;
    // O(1)
}

template <class T>
int ArrayList<T>::size() const{
    // TODO: Trả về số ptu hiện có trong danh sách
    return count;
    // O(1)
}

template <class T>
void ArrayList<T>::clear(){
    // Xóa toàn bộ ptu trong danh sách, đặt lại count = 0, capacity = 10
    delete[] data; // chỉ cần delete mảng chứ ko cần delete từng ô (khác vs SinglyLinkedList)
    data = nullptr;
    count = 0;
    capacity = 10;
    data = new T[capacity];
    // O(1)
}

template <class T>
T& ArrayList<T>::get(int index){
    // TODO: Trả về tham chiếu (T&) đến gtri của ptu tại vị trí index (trả về ptu tại vị trí index)
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    return data[index];
    // O(1)
}

template<class T>
const T& ArrayList<T>::get(int index) const{
    // TODO: Trả về tham chiếu đến gtri của ptu tại vị trí index (trả về ptu tại vị trí index)
	if (index < 0 || index >= count) {
    	throw out_of_range("Index is invalid!");
    }
    return data[index];
}

template <class T>
void ArrayList<T>::set(int index, T e){
    // Gán lại gtri cho data tại index thành e
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }
    data[index] = e;
}

template <class T>
int ArrayList<T>::indexOf(T item) const{
    // trả về chỉ số của ptu đầu tiên có gtri bằng item, nếu ko tìm thấy trả về -1
    for (int i = 0; i < count; i++) {
        if (data[i] == item) {
            return i;
        }
    }
    return -1;
    // O(n)
}

template <class T>
bool ArrayList<T>::contains(T item) const{
    // TODO: Kiểm tra xem danh sách có chứa ptu có gtri bằng item không
    return indexOf(item) != -1;
    // O(n)
}

template <class T>
string ArrayList<T>::toString(string (*item2str)(T &)) const{
    // TODO: Trả về chuỗi biểu diễn danh sách theo định dạng [item1, item2, ..., itemN]
    // Nếu con trỏ item2str dc cung cấp => chuyển đổi từng ptu sang chuỗi bằng hàm này
    ostringstream oss;
    oss << "[";
    for (int i = 0; i < count; ++i) {
        // trong hàm const: data[i] có kiểu dữ liệu const T&
        // vì hàm toString là hàm const => mọi thành viên data[i] đều là const
        // Nhưng string (*item2str)(T&) yêu cầu tham số truyền vào là T& (ko phải const T&)
        // nên ko thể truyền data[i] trực tiếp vào hàm item2str(T&)
        if (item2str) oss << item2str(const_cast<T&>(data[i])); // loại bỏ const
        else          oss << data[i];                 // fallback mặc định
        if (i < count - 1) oss << ", ";
    }
    oss << "]";
    return oss.str();
    // O(n)
}

// Class Iterator methods
template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin() {
    // TODO: Trả về iterator trỏ đến ptu đầu tiên của danh sách
    return Iterator(this, 0); // ptu đầu là pList, ptu 2 là cursor
    // O(1)
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end() {
    // TODO: Trả về iterator trỏ đến vị trí sau ptu cuối cùng của danh sách
    return Iterator(this, count);
    // O(1)
}

// ----------------- Iterator of ArrayList Implementation -----------------
// Chức năng của lớp Iterator: Duyệt tuần tự các ptu trong ds mảng động
// - Mỗi iterator lưu trữ con trỏ đến ArrayList và chỉ số hiện tại (cursor) trong ds 
// => cho phép truy cập ptu tại vị trí đó, và tiến tới ptu kế
// - Hỗ trợ các toán tử: *, !=, ++, --

// Iterator có 2 thuộc tính: 
// int cursor (chỉ số hiện tại): Hơp lệ từ 0 đến count. cursor = count 
// => iterator ở end() và ko có ptu để dereference (giải tham chiếu: trả về kq dc lưu tại địa chỉ đó)
// ArrayList<T>* pList (con trỏ đến ds mảng động): Để truy cập ptu trong ds
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T> *pList, int index){
    // Khởi tạo iterator trỏ vào mảng pList tại index
    this->pList = pList;
    if (pList) {
        // Kiểm tra index hợp lệ
        if (index < 0 || index > pList->count) throw out_of_range("Index is invalid!");
    }
    this->cursor = index;
}

// typename báo cho compiler biết từ khóa phái sau nó (Iterator) là 1 kiểu chứ ko phải biến
template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator=(const ArrayList<T>::Iterator &other){
    // gán trạng thái từ iterator other sang iterator hiện tại
    if (this != &other){
        // do this là con trỏ => phải dùng '->'
        // hoặc nếu muốn dùng '.' thì phải dereference: (*this).pList = ...
        // còn other là tham chiếu (do có &) => phải dùng '.'
        this->pList = other.pList;
        this->cursor = other.cursor; // Copy index
        // vậy nếu ta ghi *this = other; thì sao?
        // => Lỗi vì *this là tham chiếu đến đối tượng hiện tại, ko thể gán trực tiếp tham chiếu này cho other (là tham chiếu khác)
        // *this là 1 đối tượng, ko phải con trỏ (do đã dereference)
    }
    return *this;
}

template <class T>
T &ArrayList<T>::Iterator::operator*(){
    // trả về tham chiếu đến ptu tại vị trí cursor trong pList
    if (pList == nullptr || cursor < 0 || cursor >= pList->count){
        // Nếu dereference khi iterator ở end() hoặc pList rỗng => ném ngoại lệ
        throw out_of_range("Iterator is out of range!");
    }
    return pList->data[cursor]; // Access 'data' using 'cursor'
}

template <class T>
bool ArrayList<T>::Iterator::operator!=(const typename ArrayList<T>::Iterator &other) const{
    // so sánh sự khác nhua của 2 iterator
    // 2 iterator gọi là khác nhua nếu khác cursor hoặc khác pList
    return (this->pList != other.pList || this->cursor != other.cursor); // Compare 'index'
}

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator++(){
    // Tiến tới otu kế tiếp trong pList (tiền tố)
    if (pList == nullptr || cursor >= pList->count){
        // Nếu advance khi iterator ở end() (cursor = count) hoặc pList rỗng => ném ngoại lệ
        throw out_of_range("Iterator cannot advance past end!");
    }
    cursor++; // Increment 'index'
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int){
    // Tiến tới otu kế tiếp trong pList (ậu tố) và trả về bản sao gtri cũ
    if (pList == nullptr || cursor >= pList->count){
        // Nếu advance khi iterator ở end() (cursor = count) hoặc pList rỗng => ném ngoại lệ
        throw out_of_range("Iterator cannot advance past end!");
    }

    Iterator temp = *this;
    ++(*this);
    return temp;
}

// Như vậy có 2 hàm operator++: nếu có int => tiếp tới ptu kế và trả về bản sao gtri cũ
// còn nếu ko có int => chỉ tiến tới ptu kế tiếp torng mảng
// Cả 2 đều ném ngoại lệ: Iterator cannot advance past end!

template <class T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator--(){
    // Lùi về otu ptu trước đó trong pList (tiền tố)
    // Nếu iterator đang ở vị trí đầu => ném ngoại lệ :Iterator cannot move before begin!
    if (!pList || cursor == 0) throw out_of_range("Iterator cannot move before begin!");
    if (cursor > pList->count) throw out_of_range("Iterator is out of range!");
    if (cursor == pList->count) cursor = pList->count - 1; // từ end() lùi về phần tử cuối
    else --cursor;
    return *this;
}

template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int){
    // Lùi về otu ptu trước đó trong pList (hậu tố) và trả về bản sao gtri cũ
    // Nếu iterator đang ở vị trí đầu => ném ngoại lệ :Iterator cannot move before begin!
    if (!pList || cursor == 0) throw out_of_range("Iterator cannot move before begin!");
    if (cursor > pList->count) throw out_of_range("Iterator is out of range!");
    Iterator temp = *this;
    --(*this);
    return temp;
}

// ----------------- SinglyLinkedList Implementation -----------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList(){
    // TODO: Khởi tạo SLL rỗng 
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList(){
    // TODO: Hàm hủy giải phóng toàn bộ vùng nhớ đã cấp phát cho các nút trong SLL
    this->clear();
}

// TODO: implement other methods of SinglyLinkedList
template <class T>
void SinglyLinkedList<T>::add(T e){
    // Thêm ptu e vào cuối danh sách
    Node* n = new Node(e);
    if (!head) head = tail = n;
    else tail = tail->next = n;
    count++;
    // O(n), có thể tối ưu thành O(1) bằng cách lưu con trỏ tail
}

template <class T>
void SinglyLinkedList<T>::add(int index, T e){
    // Chèn ptu có gtri e vào vị trí index
    // Với SLL thì ko cần dịch phải các ptu phía sau như trong mảng động 
    // mà chỉ cần cập nhật lại các con trỏ next
    if (index < 0 || index > count){
        throw out_of_range("Index is invalid!");
    }
    Node *newNode = new Node(e);
    if (index == 0){
        // thêm ở đầu => Node mới trỏ đến head cũ và cập nhật head mới
        newNode->next = head;
        head = newNode;
        if (count == 0){
            tail = newNode;
        }
    }
    else {
        Node *current = head;
        for (int i = 0; i < index - 1; i++){
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (newNode->next == nullptr){
            // Nếu thêm vào cuối => cập nhật tail
            tail = newNode;
        }
    }
    count++;
    // O(n)
}

template <class T>
T SinglyLinkedList<T>::removeAt(int index){    
    // xóa ptu tại vị trí index và trả về gtri của ptu đó 
    if (index < 0 || index >= count) {
        throw out_of_range("Index is invalid!");
    }

    Node *prev = nullptr, *cur = head;
    for (int i = 0; i < index; ++i) { 
        prev = cur; 
        cur = cur->next; 
    }
    T val = cur->data;
    // prev == nullptr (ko có ptu trc đó => cur là ptu đầu) 
    // => gán head ptu kế tiếp của cur (xóa đầu)
    if (!prev) head = cur->next;        
    else       prev->next = cur->next;
    
    if (cur == tail) tail = prev;
    delete cur;
    
    --count;
    if (count == 0) head = tail = nullptr;
    return val;
    // O(n)
}

template <class T>
bool SinglyLinkedList<T>::removeItem(T item){
    // Xóa nút đầu tiên có gtri bằng item
    // trả về true nếu xóa thành công, false nếu ko tìm thấy
    Node *prev = nullptr, *cur = head;
    while (cur && !(cur->data == item)) { 
        prev = cur; 
        cur = cur->next; 
    }

    if (!cur) return false;
    if (!prev) head = cur->next; 
    else       prev->next = cur->next;

    if (cur == tail) tail = prev;
    delete cur;
    --count;
    if (!head) tail = nullptr;
    return true;
    // O(n)
}

template <class T>
bool SinglyLinkedList<T>::empty() const{
    // Kiểm tra xem danh sách có rỗng không
    return count == 0;
    // O(1)
}

template <class T>
int SinglyLinkedList<T>::size() const{
    // trả về số lượng ptu hiện tại của SLL
    return count;
    // O(1)
}

template <class T>
void SinglyLinkedList<T>::clear(){
    // Xóa toàn bộ ptu trong SLL
    for (Node* p = head; p != nullptr; ) {
        Node* nxt = p->next;
        delete p;
        p = nxt;
    }
    // ❌ CÁCH SAI
    // for (Node* p = head; p != nullptr; p = p->next) {
    //     delete p;  // Giải phóng p
    //     // p = p->next; // LỖI! p đã bị delete, không thể truy cập p->next
    // }
    head = tail = nullptr;
    count = 0;
    // O(n) vì phải duyệt qua và xóa từng nút
}

template <class T>
T &SinglyLinkedList<T>::get(int index){
    // lấy gtri của ptu tại chỉ số index trong SLL
    if (index < 0 || index >= count) throw out_of_range("Index is invalid!");
    Node* p = head;
    for (int i = 0; i < index; ++i) p = p->next;
    return p->data;
    // O(n)
}

template <class T>
const T &SinglyLinkedList<T>::get(int index) const{
    if (index < 0 || index >= count) throw out_of_range("Index is invalid!");
    Node* p = head;
    for (int i = 0; i < index; ++i) p = p->next;
    return p->data;
}

template <class T>
int SinglyLinkedList<T>::indexOf(T item) const{
    // trả về chỉ số của ptu đầu tiên có gtri item trong SLL
    // nếu ko tìm thấy trả về -1
    Node *current = head;
    int index = 0;
    while (current != nullptr){
        if (current->data == item){
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
    // O(n)
}

template <class T>
bool SinglyLinkedList<T>::contains(T item) const{
    // kiểm tra xem danh sách có ptu nào chứa gtri = item không
    return this->indexOf(item) != -1;
    // O(n)
}

template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T &)) const {
    // trả về chuỗi biểu diễn của toàn bộ danh sách theo định dạng: [item1]->[item2]->...->[itemN]
    // Nếu item2str dc cung cấp => chuyển đổi từng ptu sang chuỗi bằng hàm này
    // nếu ko, dùng toán tử << mặc định
    ostringstream oss;
    Node* cur = head;
    bool first = true;
    while (cur != nullptr) {
        if (!first) oss << "->";
        oss << "[";
        if (item2str) oss << item2str(cur->data);
        else          oss << cur->data;      // fallback mặc định
        oss << "]";
        cur = cur->next;
        first = false;
    }
    return oss.str();
    // O(n)
}

// Lớp Iterator có 1 thuộc tính: int current (con trỏ đến nút hiện tại trong SLL)
template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin(){
    // trả về iterator trỏ đến ptu đầu của SLL
    return Iterator(head); 
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end(){
    // trả về Iterator trỏ đến sau ptu cuối (nullptr)
    return Iterator(nullptr); 
}

// ----------------- Iterator of SinglyLinkedList Implementation -----------------
// TODO: implement other methods of SinglyLinkedList::Iterator
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node *node){
    // khởi tạo iterator trỏ đến nút node trong danh sách
    this->current = node;
}

template <class T>
typename SinglyLinkedList<T>::Iterator &SinglyLinkedList<T>::Iterator::operator=(const Iterator &other){
    // gán iterator other cho iterator hiện tại
    if (this != &other){
        this->current = other.current; // chỉ copy 1 đối utượng Node*
    }
    return *this; // trả về tham chiếu của đối tượng hiện tại
    // O(1)
}

template <class T>
T &SinglyLinkedList<T>::Iterator::operator*(){
    // trả về tham chiếu đến gtri của nút hiện tại mà iterator trỏ đến
    if (current == nullptr){
        throw out_of_range("Iterator is out of range!");
    }
    return current->data;
}

template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator &other) const{
    return this->current != other.current;
}

template <class T>
typename SinglyLinkedList<T>::Iterator &SinglyLinkedList<T>::Iterator::operator++(){
    // Tiến tới nút kế tiếp trong SLL và trả về tham chiếu đến iterator hiện tại
    if (current == nullptr) {
        throw out_of_range("Iterator cannot advance past end!");
    }
    current = current->next;
    return *this;
}
// khác với array list: tiến tới ptu kế tiếp chứ ko trả về gì cả

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int){
    // Tiến tới nút kế tiếp trong SLL và trả về bản sao gtri cũ
    if (current == nullptr) {
        throw out_of_range("Iterator cannot advance past end!");
    }
    Iterator temp = *this;
    ++(*this);
    return temp; // bản sao gtri cũ (do hiện tại *this đang chứa gtri mới là gtri hiện tại sau khi ++)
}

// ----------------- VectorStore Implementation -----------------
// Chức năng của lớp VectorStore: 
// - Lưu trữ và truy vấn các vector nhiều chiều và dc nhúng từ các đoạn văn bản
// - hỗ trợ phép truy vấn tìm kiếm dựa trên độ tương đồng cosine similarity giữa vector truy vấn và các vector đã lưu trữ
// - Sử dụng ArrayList để lưu trữ các VectorRecord
// - Mỗi VectorRecord chứa: id (int), rawText (string), rawLength (int), vector (SinglyLinkedList<float>*)

// - Mỗi VectorStore có các cơ chế cơ bản sau:
// Embbedding:  Dữ liệu thô (raw data), chẳng hạn một chuỗi văn bản, 
// trước tiên sẽ được biến đổi thành một vector số thực nhờ một hàm nhúng, 
// vector này thường sẽ có số chiều cố định đối với từng loại VectorStore

// Lưu trữ: Sau khi một vector được sinh ra, VectorStore sẽ lưu trữ vector đó kèm với các
// dữ liệu mô tả (metadata) - chính là các thuộc tính của VectorRecord

// Duyệt và xử lý hàng loạt: VectorStore cho phép duyệt qua toàn bộ vector đã lưu để
// áp dụng các thao tác chung như tính toán độ tương đồng, lọc theo điều kiện, hoặc trích xuất thông tin

// Tìm kiếm tương tự (Similarity Search): Khi nhận một truy vấn (query), 
// trước tiên query cũng được biến đổi thành vector số thực. 
// Sau đó, VectorStore sẽ so sánh query với toàn bộ vector trong kho bằng một thước đo độ tương đồng. 
// Cuối cùng, VectorStore sẽ trả về vector gần nhất, hoặc danh sách k vector gần nhất
VectorStore::VectorStore(int dimension, EmbedFn embeddingFunction) {
    // TODO: khởi tạo 1 kho rỗng để lưu trữ các vector có số chiều cố định và gắn hàm nhúng ban đầu
    // VectorStore thực chất là 1 kho lưu trữ các bản ghi VectorRecord - gòm các vector số thực nhiều chiều và metadata
    this->dimension = dimension; // số chiều của mọi vector trong kho
    this->embeddingFunction = embeddingFunction; // hàm nhúng văn bản thành vector, kiểu trả về là con trỏ đến SinglyLinkedList<float>
    this->count = 0;
    this->records = ArrayList<VectorRecord*>();
    this->nextId = 1; // id tiếp theo sẽ gán cho bản ghi mới
}

VectorStore::~VectorStore() {
    // TODO: giải phóng toàn bộ vùng nhớ đã cấp phát cho các vector và metadata trong kho
    for (int i = 0; i < records.size(); i++) {
        delete records.get(i)->vector;
        delete records.get(i);
    }
    records = ArrayList<VectorRecord*>();
    dimension = 0;
    count = 0;
    embeddingFunction = nullptr; // vì là con trỏ nên phải gán nullptr
}

// TODO: implement other methods of VectorStore
VectorStore::VectorRecord::VectorRecord(int id, const string &rawText, SinglyLinkedList<float> *vector){
    this->id = id;                          // định danh duy nhất
    this->rawText = rawText;                // đoạn văn bản gốc
    this->rawLength = rawText.length();     // độ dài đoạn văn bản gốc (số ký tự)
    this->vector = vector;                  // vector số thực nhiều chiều có dc sau khi nhúng văn bản tương ứng
}

int VectorStore::size() const{
    // vì records chứa nhiều vector => trả về số lượng vector hiện có của records
    return records.size();
}

bool VectorStore::empty() const{
    // kiểm tra xem records có rỗng ko
    return records.empty();
}

void VectorStore::clear(){
    // Xóa toàn bộ vector và metadata trong kho
    for (int i = 0; i < records.size(); i++) {
        delete records.get(i)->vector;
        delete records.get(i);
    }
    records.clear();
    count = 0;
    nextId = 1;
    // O(n)
}

SinglyLinkedList<float> *VectorStore::preprocessing(string rawText){
    // tiền xử lý đoạn văn bản rawText thành vector số thực nhiều chiều
    if (!embeddingFunction) return nullptr;
    // Yều cầu: 
    // - Gọi embeddingFunction để nhúng rawText thành vector
    // - Nếu vector thu được đủ dimension thì giữ nguyên
    // - Nếu vector thu được vượt dimension thì cắt bớt các giá trị thừa ở cuối
    // - Nếu vector thu được ko đủ dimension thì bổ sung các giá trị 0.0f vào cuối
    SinglyLinkedList<float>* src = embeddingFunction(rawText); // chuyển rawText thành vector số thực nhiều chiều
    if (!src) return nullptr; // nếu ko có ptu nào trong vector nguồn => trả về nullptr

    // tạo linked list đích đúng dimension theo O(d)
    SinglyLinkedList<float>* out = new SinglyLinkedList<float>();
    // duyệt SLL bằng iterator
    auto it = src->begin(); // con trỏ iterator đến đầu linked list nguồn, kiểu dữ liệu auto: cho phép compiler tự động suy luận kiểu dữ liệu dựa trên giá trị gán
    auto itEnd = src->end(); // con trỏ iterator đến cuối linked list nguồn (sau ptu cuối)
    for (int i = 0; i < dimension; ++i) {
        float val = 0.0f; // mặc định, nếu hết ptu nào thì gán 0.0f vào cuối đến khi đủ số chiều
        if (it != itEnd) { 
            val = *it; 
            ++it; 
        }
        out->add(val); // thêm val vào linked list đích
    }
    delete src; // tránh leak nếu embeddingFunction cấp phát
    return out; // trả về output SLL có số chiều đúng dimension
    // O(dimension)
}

void VectorStore::addText(string rawText){
    // Thêm đoạn văn bản rawText vào kho, bao gồm:
    // - tiền xử lý rawText thành vector số thực nhiều chiều bằng hàm preprocessing
    SinglyLinkedList<float>* vec = preprocessing(rawText);
    // Nếu ko thể tiền xử lý (vector trả về là nullptr) => ko thêm gì cả
    if (!vec) return;
    // - tạo bản ghi VectorRecord mới với id tiếp theo, rawText và vector thu được
    VectorRecord* record = new VectorRecord(nextId, rawText, vec);
    // - thêm bản ghi vào records
    records.add(record);
    // - cập nhật count và nextId
    ++count;
    ++nextId;
    // O(n + d) với n là số bản ghi hiện có, d là dimension
}

SinglyLinkedList<float> &VectorStore::getVector(int index){
    // truy xuất tham chiếu đến vector tại vị trí index trong kho (arraylist records)
    if (index < 0 || index >= records.size()) {
        throw out_of_range("Index is invalid!");
    }
    return *(records.get(index)->vector); // trả về tham chiếu đến vector: nghĩa là hám này sẽ nhận địa chỉ của vector trong bộ nhớ 
    // => mọi thay đổi trên tham chiếu này sẽ ảnh hưởng trực tiếp đến vector gốc trong kho
    // O(1)
}

string VectorStore::getRawText(int index) const{
    // truy xuất đoạn văn bản gốc tại vị trí index trong kho
    if (index < 0 || index >= records.size()) {
        throw out_of_range("Index is invalid!");
    }
    return records.get(index)->rawText; 
    // O(1)
}

int VectorStore::getId(int index) const{
    // truy xuất id của bản ghi tại vị trí index trong kho
    if (index < 0 || index >= records.size()) {
        throw out_of_range("Index is invalid!");
    }
    return records.get(index)->id; 
    // O(1)
}

bool VectorStore::removeAt(int index){
    // Xóa bản ghi vector và metadata tại vị trí index trong kho, bao gồm:
    // - kiểm tra index hợp lệ
    if (index < 0 || index >= records.size()) {
        throw out_of_range("Index is invalid!");
    }
    // - xóa bản ghi tại index khỏi records
    VectorRecord* record = records.removeAt(index);
    // - giải phóng bộ nhớ đã cấp phát cho vector đã khai báo động và metadata trong bản ghi đó
    delete record->vector;
    // xóa record đó ra khỏi VectorStore
    delete record;
    // - cập nhật count và nextId
    count--;
        
    // Không cập nhật lại id các bản ghi còn lại!
    // Tính MAXID sau khi xóa để tính lại NEXTID = MAXID + 1 => tránh trùng lặp id
    int maxId = 0;
    for (int i = 0; i < records.size(); ++i) {
        int curId = records.get(i)->id;
        if (curId > maxId) maxId = curId;
    }
    nextId = (records.empty() ? 1 : (maxId + 1));
    return true;
}

bool VectorStore::updateText(int index, string newRawText){
    // Cập nhật văn bản gốc tại vị trí index trong kho thành newRawText, 
    // giữ nguyên id, cập nhật lại các thuộc tính khác của record
    if (index < 0 || index >= records.size()) {
        throw out_of_range("Index is invalid!");
    }
    // tiền xử lý chuỗi mới newRawText thành vector số thực nhiều chiều
    SinglyLinkedList<float>* newVec = preprocessing(newRawText);
    VectorRecord* record = records.get(index); // lấy bản ghi tại index
    delete record->vector; // Free old vector: giải phóng bộ nhớ đã cấp phát cho vector cũ
    record->rawText = newRawText;
    record->rawLength = newRawText.length();
    record->vector = newVec;
    return true;
    // O(n)
}

void VectorStore::setEmbeddingFunction(EmbedFn newEmbeddingFunction){
    // Cập nhật hàm nhúng mới cho VectorStore
    this->embeddingFunction = newEmbeddingFunction;
    // O(1)
}

void VectorStore::forEach(void (*action)(SinglyLinkedList<float> &, int, string &)){
    // Duyệt toàn bộ các vector trong kho và áp dụng hàm action cho từng vector
    for (int i = 0; i < records.size(); i++) {
        VectorRecord* record = records.get(i);
        action(*(record->vector), record->rawLength, record->rawText);
    }
    // O(n)
}

double VectorStore::cosineSimilarity(const SinglyLinkedList<float> &v1, const SinglyLinkedList<float> &v2) const{
    // tính độ tương đồng cosine giữa 2 vector v1 và v2
    auto &aList = const_cast<SinglyLinkedList<float>&>(v1);
    auto &bList = const_cast<SinglyLinkedList<float>&>(v2);
    auto itA = aList.begin(), endA = aList.end();
    auto itB = bList.begin(), endB = bList.end();

    double dot = 0.0, n1 = 0.0, n2 = 0.0;
    for (int i = 0; i < dimension; ++i) {
        // các biến a và b là giá trị của ptu hiện tại trong v1 và v2 tương ứng
        double a = (itA != endA) ? (double)*itA++ : 0.0;
        double b = (itB != endB) ? (double)*itB++ : 0.0;
        dot += a*b; // tích vô hướng
        n1 += a*a; n2 += b*b;
    }
    if (n1 == 0.0 || n2 == 0.0) return 0.0;
    return dot / (sqrt(n1)*sqrt(n2));
    // O(dimension)
}

double VectorStore::l1Distance(const SinglyLinkedList<float> &v1, const SinglyLinkedList<float> &v2) const{
    // tính khoảng cách L1 (Manhattan) giữa 2 vector v1 và v2
    // = sum(|v1_i - v2_i|)
    auto &aList = const_cast<SinglyLinkedList<float>&>(v1);
    auto &bList = const_cast<SinglyLinkedList<float>&>(v2);
    auto itA=aList.begin(), endA=aList.end();
    auto itB=bList.begin(), endB=bList.end();

    double sum=0.0;
    for (int i=0;i<dimension;++i) {
        double a=(itA!=endA)? (double)*itA++ : 0.0;
        double b=(itB!=endB)? (double)*itB++ : 0.0;
        double d=a-b; 
        if (d<0) d=-d; 
        sum+=d;
    }
    return sum;
    // O(dimension)
}

double VectorStore::l2Distance(const SinglyLinkedList<float> &v1, const SinglyLinkedList<float> &v2) const{
    auto &aList = const_cast<SinglyLinkedList<float>&>(v1);
    auto &bList = const_cast<SinglyLinkedList<float>&>(v2);
    auto itA=aList.begin(), endA=aList.end();
    auto itB=bList.begin(), endB=bList.end();

    double sum=0.0;
    for (int i=0;i<dimension;++i) {
        double a=(itA!=endA)? (double)*itA++ : 0.0;
        double b=(itB!=endB)? (double)*itB++ : 0.0;
        double d=a-b; 
        sum += d*d;
    }
    return sqrt(sum);
}

int VectorStore::findNearest(const SinglyLinkedList<float> &query, const string &metric) const {
    // Tìm chỉ số của vector gần nhất với vector truy vấn query,
    // sử dụng độ đo khoảng cách metric để tính tương đồng giữa vector truy vấn và các vector trong kho
    if (records.empty()) return -1;

    // chuẩn hóa metric
    string use = metric;
    if (use == "euclidean") use = "l2";
    else if (use == "manhattan") use = "l1";
    else if (!(use == "cosine" || use == "l1" || use == "l2")) throw invalid_metric();

    int bestIdx = -1;       // chỉ số của vector gần nhất
    double bestKey = 0.0;   // điểm đánh giá tốt nhất (nhỏ nhất)
    bool first = true;      // cờ để đánh dấu lần lặp đầu tiên

    const bool isCos = (use == "cosine");
    const int n = records.size();
    const double dis = 1e-9;  // sai số so sánh float

    // duyệt toàn bộ vector trong kho để tìm vector gần nhất
    for (int i = 0; i < n; ++i) {
        const SinglyLinkedList<float> &v = *(records.get(i)->vector);
        // tính điểm đánh giá bằng số đo khoảng cách tương ứng
        double val = isCos ? cosineSimilarity(query, v)
                        : (use == "l1" ? l1Distance(query, v) : l2Distance(query, v));

        // kẹp về [-1,1] cho cosine để tránh >1 do sai số
        if (isCos) {
            if (val > 1.0) val = 1.0;
            else if (val < -1.0) val = -1.0;
        }

        double key = isCos ? -val : val;  // minimize key

        // cập nhật best với dis + tie-break theo index nhỏ hơn
        if (first || key < bestKey - dis || (!first && abs(key - bestKey) <= dis && i < bestIdx)) {
            bestKey = key;
            bestIdx = i;
            first = false;
        }
    }
    return bestIdx;
    // O(n x dimension) do phải duyệt n vector, mỗi vector có dimension chiều
}

int* VectorStore::topKNearest(const SinglyLinkedList<float> &query, int k, const string &metric) const {
    // 1) Validate metric FIRST (để test_169 pass)
    string use = metric;
    if (use == "euclidean") use = "l2";
    else if (use == "manhattan") use = "l1";
    else if (use == "cosine" || use == "l1" || use == "l2") { /* ok */ }
    else throw invalid_metric();

    // 2) Validate k AFTER metric
    if (k <= 0 || k > records.size()) throw invalid_k_value();

    const bool isCos = (use == "cosine");
    const int n = records.size();

    // 3) Tính điểm: key nhỏ hơn = tốt hơn
    struct ScoreIndex { double key; int idx; }; // lưu điểm và chỉ số
    // mảng lưu điểm và chỉ số tương ứng
    ScoreIndex *arr = new ScoreIndex[n]; // n là số vector trong kho
    // duyệt toàn bộ vector trong kho để tính điểm khoảng cách tương đồng
    for (int i = 0; i < n; ++i) {
        const SinglyLinkedList<float> &v = *(records.get(i)->vector);
        double val = isCos ? cosineSimilarity(query, v)
                        : (use == "l1" ? l1Distance(query, v) : l2Distance(query, v));
        arr[i].key = isCos ? -val : val;   // cosine dùng -similarity (giải thích trong phần dưới)
        arr[i].idx = i;                    // tie-break theo index tăng dần
    }

    // 4) Quicksort lặp: key tăng dần; nếu "gần bằng" -> idx tằng dần => vector gần nhất ở đầu mảng
    // LƯU Ý: 
    // Nếu key là khoảng cách thì key nhỏ hơn (khoảng cách nhỏ hơn) đứng đầu mảng
    // Còn nếu key là độ tương đồng thì key lớn hơn (độ tương đồng lớn hơn) đứng đầu mảng \
    mà ở đây key lại dc lưu tăng dần => độ tương đồng nhỏ nhất ở đầu \
    => phải lưu similarity về số âm để key nhỏ nhất là độ tương đồng lớn nhất
    struct Range { int l, r; }; // lưu phạm vi sắp xếp: chỉ số bắt đầu và kết thúc
    Range *stack = new Range[n];
    int top = 0; stack[top++] = {0, n - 1}; // đẩy toàn bộ màng vào stack
    
    auto swapSI = [](ScoreIndex &a, ScoreIndex &b){ ScoreIndex t=a; a=b; b=t; };
    const double dis = 1e-9;

    auto lessThan = [dis](const ScoreIndex &a, double pk, int pi){
        if (a.key < pk - dis) return true;
        if (a.key > pk + dis) return false;
        return a.idx < pi; // gần bằng nhau -> index nhỏ hơn đứng trước
    };
    auto greaterThan = [dis](const ScoreIndex &a, double pk, int pi){
        if (a.key > pk + dis) return true;
        if (a.key < pk - dis) return false;
        return a.idx > pi;
    };

    while (top) {
        Range cur = stack[--top];
        int l = cur.l, r = cur.r;
        if (l >= r) continue;

        int mid = (l + r) >> 1;
        double pk = arr[mid].key; int pi = arr[mid].idx;

        int i = l, j = r;
        while (i <= j) {
            while (lessThan(arr[i], pk, pi)) ++i;
            while (greaterThan(arr[j], pk, pi)) --j;
            if (i <= j) { swapSI(arr[i], arr[j]); ++i; --j; }
        }
        if (l < j) stack[top++] = {l, j};
        if (i < r) stack[top++] = {i, r};
    }
    delete[] stack;

    // 5) Trả top-k chỉ số
    int *result = new int[k];
    for (int i = 0; i < k; ++i) result[i] = arr[i].idx;
    delete[] arr;
    return result; // do phải trả về mảng các id của k vector gần vector truy vấn
    // O(n x d + nlogn) : tính điểm O(n x d) + sắp xếp quicksort O(nlogn)
}

// Explicit template instantiation for char, string, int, double, float, and Point
template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
