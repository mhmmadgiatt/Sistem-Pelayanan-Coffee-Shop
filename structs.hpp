// file header untuk struct

// FUNGSI-FUNGSI
void _inisialisasiMenuPreset();  // inisialisasi menu pesanan bawaan/preset
void printMenu();                // print menu pesanan coffe shop
string getTime();                // fungsi untuk generate timestamp

struct Layanan;
template<typename T>
struct List;
template<typename T>
struct ListQueue;
struct PesananCoffeeShop;
struct action;
template<typename T>
struct Stack;
struct SalesReport;
struct DataPelanggan;
struct PesananPelanggan;

struct action{
    std::function<int()> undo, redo;
    action *next = nullptr;

    action(){
    }
};

// fungsi untuk traversal laporan penjualan
void traversalReport(List<DataPelanggan> &listPelanggan);
template<typename T, typename LT>
void pushDeleteAction(T *node, int index, LT list);

template<typename T>
struct Stack{
    T *top = nullptr;
    void push(T *&newNode){
        newNode->next = top;
        top = newNode;
    }
    T* pop(T *node = nullptr){
        if(!top) return nullptr;
        node = top;
        top = top->next;
        return node;
    }
    T* pop(Stack &stack){
        T *node;
        if(!top) return nullptr;
        node = top;
        top = top->next;
        stack.push(node);
        return node;
    }
    void clear(){
        T *pDelete;
        while(top){
            pDelete = top;
            top = top->next;
            free(pDelete);
        }
        top = nullptr;
    }
};

Stack<action> UndoStack, RedoStack;

// struct untuk struktur data queue
template<typename T>
struct ListQueue{
    // iterator untuk fungsi operator[]
    // index untuk operator
    T *head = nullptr;
    T *tail = nullptr;

    //constructor
    ListQueue(){
    }
    //copy assignment
    void operator=(const ListQueue &ref){
        clear();
        T *pHelp = ref.head;
        while(pHelp){
            push_back(*pHelp);
            pHelp = pHelp->next; 
        }
    }
    int index(T *node){
        T *pHelp = head;
        int count = 0;
        while(pHelp && pHelp != node){
            count++;
            pHelp = pHelp->next;
        }
        if(!pHelp) return-1;
        return count;
    }
    void push_back(T node){
        T *pNode = new T;
        *pNode = node;
        enqueue(pNode);
    }
    int size(){
        T *pHelp = head;
        int count = 0;
        while(pHelp){
            count++;
            pHelp = pHelp->next;
        }
        return count;
    }
    //destructor
    void clear(){
        T *pDelete;
        while(head){
            pDelete = head;
            head = head->next;
            free(pDelete);
        }
        delete pDelete;
        head = nullptr;
        tail = nullptr;
    }
    //true if queue empty
    bool empty(){
        if(head == nullptr) return true;
        return false;
    }
    //fungsi untuk menghapus node pada index tertentu
    void remove(int index, bool isDestructive  = 1){
        T *pHelp = head, *pDelete = head;
        if(index == 0){
            if(head){
                if(tail == head) tail = tail->next;
                head = head->next;
                if(isDestructive) delete pDelete;
                return;
            }
            else return;
        }
        for(int i=0;i<index;i++){
            pHelp = pDelete;
            pDelete = pDelete->next;
        }
        if(pDelete == tail){
            if(isDestructive) delete pDelete;
            pHelp->next = nullptr;
            tail = pHelp;
        }
        pHelp->next = pDelete->next;
        if(isDestructive) delete pDelete;
    }
    void insert(int index, T *node){
        node->next = nullptr;
        if(index == 0){
            node->next = head;
            head = node;
            return;
        }
        T *pPrev = head, *pHelp = head;
        for(int i = 0;i < index;i++){
            pPrev = pHelp;
            pHelp = pHelp->next;
        }
        if(!pHelp){
            pPrev->next = node;
            tail = node;
            return;
        }
        pPrev->next = node;
        node->next = pHelp;
        return;
    }
    // fungsi untuk enqueue dengan skala prioritas yang diambil dari fungsi priority() pada node
    void priority_enqueue(T *newNode){
        newNode->priority();
        T *pPrev = nullptr;
        T *pHelp = head;
        if (head == nullptr || tail == nullptr){
            head = newNode;
            tail = newNode;
            return;
        }
        else {
            while (newNode->priority() <= pHelp->priority()){
                if (pHelp->next == nullptr){
                    break;
                }
                pPrev = pHelp;
                pHelp = pHelp->next;
            }
            if (pHelp == head && newNode->priority() > pHelp->priority()){

                newNode->next = pHelp;
                head = newNode;
            }
            else if (pHelp == tail && newNode->priority() <= pHelp->priority()){
                pHelp->next = newNode;
                tail = newNode;
            }
            else {
                pPrev->next = newNode;
                newNode->next = pHelp;
            }
        }
    }
    // fungsi untuk enqueue tanpa skala prioritas
    void enqueue(T *newNode){
        if (head == nullptr && tail == nullptr){
            head = newNode;
            tail = newNode;
            return;
        }
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
    }
    // fungsi untuk dequeue antrian
    T *dequeue(T *&temp = nullptr){
        temp = head;
        if (head == nullptr && tail == nullptr){
            temp = nullptr;
        }
        else if (head->next == nullptr){
            head = nullptr;
            tail = nullptr;
        }
        else{
            temp = head;
            head = head->next; 
        }
        temp->next = nullptr;
        return temp;
    }
    //operator untuk memakai index
    T* operator[](int index){
        T *iterator = nullptr;
        int iteratorIndex = 0;
        if(index < 0) return nullptr;
        if(iteratorIndex > index || !iterator){ // jika iterator lebih dari index atau null 
            iteratorIndex = 0;
            iterator = head;
        }
        while(iteratorIndex < index && iterator != nullptr){
            iterator = iterator->next;
            iteratorIndex++;
        }
        return iterator;
    }
};

// struct untuk struktur data linked list
template<typename T>
struct List{
    // iterator untuk fungsi operator[]
    T *head = nullptr;
    //constructor
    List(){
    }
    //copy constructor
    List(const List &ref){
        clear();
        T *pHelp = ref.head;
        while(pHelp){
            push_back(*pHelp);
            pHelp = pHelp->next; 
        }
    }
    void operator=(const List &ref){
        clear();
        T *pHelp = ref.head;
        while(pHelp){
            push_back(*pHelp);
            pHelp = pHelp->next; 
        }
    }
    int index(T *node){
        T *pHelp = head;
        int count = 0;
        while(pHelp && pHelp != node){
            count++;
            pHelp = pHelp->next;
        }
        if(!pHelp) return -1;
        return count;
    }
   void push_back(T node){
        T *pNode = new T;
        *pNode = node;
        push_back(pNode);
    }
    int size(){
        T *pHelp = head;
        int count = 0;
        while(pHelp){
            count++;
            pHelp = pHelp->next;
        }
        return count;
    }
    //destructor
    void clear(){
        T *pDelete;
        while(head){
            pDelete = head;
            head = head->next;
            free(pDelete);
        }
        delete pDelete;
        head = nullptr;
    }
    // hapus node di index
    void remove(int index,  bool isDestructive  = 1){
        T *pHelp = head, *pDelete = head;
        if(index == 0){
            if(head){
                head = head->next;
                if(isDestructive) delete pDelete;
                return;
            }
            else return;
        }
        for(int i=0;i<index;i++){
            pHelp = pDelete;
            pDelete = pDelete->next;
        }
        pHelp->next = pDelete->next;
        if(isDestructive) delete pDelete;
    }
    void insert(int index, T *node){
        node->next = nullptr;
        if(index == 0){
            node->next = head;
            head = node;
            return;
        }
        T *pPrev = head, *pHelp = head;
        for(int i = 0;i < index;i++){
            pPrev = pHelp;
            pHelp = pHelp->next;
        }
        if(!pHelp){
            pPrev->next = node;
            return;
        }
        pPrev->next = node;
        node->next = pHelp;
        return;
    }
    // return true jika kosong
    bool empty(){
        if(head == nullptr) return true;
        return false;
    }
    // push back
    void push_back(T *NewNode){
        NewNode->next = nullptr;
        T *pHelp = head;

        if(!pHelp){
            head = NewNode;
            return;
        }
        while(pHelp->next){
            pHelp = pHelp->next;
        }
        pHelp->next = NewNode;
    }
    // push back
    void operator+=(T *NewNode){
        push_back(NewNode);
    }
    //return pointer ke node di index
    T* operator[](int index){
        T *iterator = nullptr;
        // index untuk operator
        int iteratorIndex = 0;
        if(index < 0) return nullptr;
        if(iteratorIndex > index || !iterator){ // jika iterator lebih dari index atau null 
            iteratorIndex = 0;
            iterator = head;
        }
        while(iteratorIndex < index && iterator != nullptr){
            iterator = iterator->next;
            iteratorIndex++;
        }
        return iterator;
    }
};

ListQueue<DataPelanggan> queuePelanggan;    // queue untuk pelanggan
ListQueue<DataPelanggan> queueCheckout;     // queue untuk checkout

// struct untuk menyimpan laporan penjualan
struct SalesReport {
    List<DataPelanggan> listPelanggan;
    // constructor
    SalesReport(){
    }

    // fungsi untuk push ke single list laporan penjualan
    void pushListReport(DataPelanggan *poppedPelanggan){
        listPelanggan += poppedPelanggan;
    }
    void traversalReport(){
        ::traversalReport(this->listPelanggan);
    }
    
};
SalesReport salesReport;

// struct untuk menyimpan data pesanan dalam menu coffe shop
struct PesananCoffeeShop {
    int nomorOrder;
    //jumlah dalam stok
    int stok = 0;
    string nama;
    float harga = 0;
    PesananCoffeeShop *next = nullptr;
    // constructor
    PesananCoffeeShop(){
        next = nullptr;
    }
    //copy constructor
    PesananCoffeeShop(const PesananCoffeeShop &ref){
        nomorOrder = ref.nomorOrder;
        stok = ref.stok;
        nama = ref.nama;
        harga = ref.harga;
        next = ref.next;
    }
    // constructor lengkap
    PesananCoffeeShop(string Nama, int Stok, int Harga){
        next = nullptr;
        nama =  Nama;
        harga = Harga;
        stok = Stok;
    }
};

List<PesananCoffeeShop> menuPesananCoffeeShop;      // list untuk menu pesanan coffe shop
PesananCoffeeShop *PRESET_PESANAN[10] = {           // preset untuk menu pesanan coffe shop
    new PesananCoffeeShop("Espresso",19,23000),
    new PesananCoffeeShop("Americano",30,25000),
    new PesananCoffeeShop("Mocchacino",20,19000),
    new PesananCoffeeShop("Vietnam Drip",32,35000),
    new PesananCoffeeShop("Fluuffy Latte",30,25000),
    new PesananCoffeeShop("Picollo Latte",27,25000),
    new PesananCoffeeShop("Air Mineral",35,5000),
    new PesananCoffeeShop("French fries",35,15000),
    new PesananCoffeeShop("Pancake",35,16000),
    new PesananCoffeeShop("Cream Puff",35,16000)
};

template<typename T, typename LT>
int removeNode(LT *list ,int index, T *node, int code = 0){
    list->remove(index,0);
    return code;
}
template<typename T, typename LT>
int addNode(LT *list ,int index, T *node, int code = 0){
    list->insert(index, node);
    return code;
}
template<typename T>
int editNode(T *oldNode, T newValue, int code = 0){
    *oldNode = newValue;
    return code;
}
template<typename T>
void pushEditAction(T *oldNode, T newValue, int code = 0){
    action *aksi = new action;
    aksi->undo = std::bind(editNode<T>, oldNode, *oldNode, code);
    aksi->redo = std::bind(editNode<T>, oldNode, newValue, code);
    UndoStack.push(aksi);
    RedoStack.clear();
}
template<typename T, typename LT>
void pushDeleteAction(T *node, LT *list, int code = 0){
    int index = list->index(node);
    action *aksi = new action;
    aksi->undo = std::bind(addNode<T, LT>, list, index, node, code);
    aksi->redo = std::bind(removeNode<T, LT>, list, index, node, code);
    UndoStack.push(aksi);
    RedoStack.clear();
}
template<typename T, typename LT>
void pushAddAction(T *node, LT *list, int code = 0){
    int index = list->index(node);
    action *aksi = new action;
    aksi->redo = std::bind(addNode<T, LT>, list, index, node, code);
    aksi->undo = std::bind(removeNode<T, LT>, list, index, node, code);
    UndoStack.push(aksi);
    RedoStack.clear();
}
// STRUCT
// struct untuk menyimpan data jenis layanan
struct Layanan {
    int priority;    //skala prioritas layanan, semakin besar semakin didahulukan
    string nama;     //nama layanan untuk di print
    float biaya;     //persenan biaya untuk layanan
    //constructor
    Layanan(string Nama, float Biaya, int Priority){
        nama = Nama;
        biaya = Biaya;
        priority = Priority;
    }
    //copy constructor
    Layanan(const Layanan &ref){
        priority = ref.priority;
        nama = ref.nama;
        biaya = ref.biaya;
    }
};
// daftar layanan yang tersedia
Layanan LAYANAN[2] = {
    Layanan("Reguler",0,1),
    Layanan("VIP",0.1f,2)
};

// struct untuk menyimpan data pesanan pesanan pelanggan
struct PesananPelanggan {
    PesananCoffeeShop *pesanan = nullptr;    //pesanan dalam menunya
    int quantity = 0;                        //jumlah yang dipesan oleh pelanggan
    PesananPelanggan *next = nullptr;
    // constructor lengkap
    PesananPelanggan(PesananCoffeeShop *Pesanan, int Quantity){
        pesanan = Pesanan;
        quantity = Quantity;
        next = nullptr;
    }
    //copy constructor
    PesananPelanggan(const PesananPelanggan &ref){
        pesanan = ref.pesanan;
        quantity = ref.quantity;
        next = ref.next;
    }
    // constructor
    PesananPelanggan(){
        next = nullptr;
    }
    // return quantity * harga pesanan
    float subtotal(){
        return quantity*pesanan->harga;
    }
};

// struct untuk menyimpan data pelanggan
struct DataPelanggan {
    int nomorOrder;
    string nama;                             //nama pelanggan
    string timestamp;                        //waktu order
    Layanan *layanan = new Layanan("",0,0);  //layanan yang dipilih pelanggan
    float biayaTotal, biayaLayanan;          //total biaya yang harus dibayar saat checkout
    List<PesananPelanggan> pesanan;          //list pesanan yang dipilih pelanggan
    DataPelanggan *next;

    // constructor
    DataPelanggan(){
        nomorOrder = globalNomorOrder;
        next = nullptr;
    }

    // return priority dari layanan sekarang
    int priority(){
        return layanan->priority;
    }
    void hapus(){
        pushDeleteAction(this, &queuePelanggan);
        UndoStack.top->redo();
    }
    
    // fungsi untuk insersi data pelanggan
    void insertDataPelanggan(){
        int count = 1;
        size_t select;
        char decision;
        cin.ignore();
        cout << "Masukkan nama pelanggan : ";
        getline(cin, nama);
        printBatas();
        timestamp = getTime();
        cout << "Jenis layanan :\n";
        for (int i=0; i<2; i++){
            cout << i+1 << " - " << LAYANAN[i].nama <<"\n";
        }
        printBatas();
        while (true){
            cout << "Pilih jenis layanan : ";
            cin >> select;
            if(cin.fail() || select > sizeof(LAYANAN)/sizeof(Layanan) || select < 1){
                fail();
                cout << "Input salah !\n";
                continue;
            }
            layanan = &LAYANAN[select-1];
            break;
        }
        
        while (true){
            system("cls");
            printBatas();
            cout << "\t\t\t   SISTEM PELAYANAN COFFEE SHOP\n";
            printBatas();
            cout << "\t\t\t      Menu Tambah Pesanan\n";
            printBatas();
            cout << "Pilih pesanan ke-" << count << "\n";
            printBatas();
            insertListPesanan();
            printBatas();
            cout << "Tambah pesanan lain ? (Y/N) : ";
            cin >> decision;
            if (decision=='Y' || decision=='y'){                
                count ++;
                continue;
            }
            else {
                countBiaya();
                
                system("cls");
                printBatas();
                cout << "\t\t\t\tDetail Pesanan\n";
                printBatas();
                printDataPelanggan();
                printBatas();
                break;
                
            }
        }
        globalNomorOrder++;
        
    }
    // fungsi untuk insersi list pesanan masing-masing pelanggan
    void insertListPesanan(){
        PesananPelanggan *newPesanan = new PesananPelanggan;
        bool isExist = 0;
        int quantity = 0;
        printMenu();
        while (true){
            int select;
            cout << "Pilih pesanan : ";
            cin >> select;
            newPesanan->pesanan = menuPesananCoffeeShop[select-1];
            for(int i = 0;pesanan[i];i++){
                if(pesanan[i]->pesanan == newPesanan->pesanan) {newPesanan = pesanan[i]; isExist = 1; break;}
            }
            if(cin.fail()){
                fail();
                cout << "Input salah !\n";
                continue;
            }
            if (!newPesanan->pesanan){
                cout << "Input salah !\n";
                continue;
            }            
            else {
                
                if ( newPesanan->pesanan->stok == 0){
                    cout << "Stok pesanan habis !\n";
                    break;
                }
                while (true){
                    cout << "Berapa banyak ? : ";
                    cin >> quantity;
                    
                    if (quantity > 0 && quantity+newPesanan->quantity <= newPesanan->pesanan->stok){
                        newPesanan->quantity += quantity;
                        break;
                    }
                    fail();
                    cout << "Input salah !\n";
                }
                break;
            }
            
        }
        if(!isExist) pesanan += newPesanan;
    }
    // fungsi untuk traversal data pesanan
    void traversalPesanan(){
        for(int i = 0;pesanan[i];i++){
            cout << "\t\t\t  " << setw(22) << left << pesanan[i]->pesanan->nama << setw(2) << left << pesanan[i]->quantity
                 << " pcs   @Rp " << setw(6) << pesanan[i]->pesanan->harga << " = Rp " << setw(6) << left
                 << pesanan[i]->subtotal() << "\n";
        }
    }
    // fungsi untuk mencatat biaya-biaya (menyimpan ke variabel)
    void countBiaya(){
        biayaLayanan = getBiayaLayanan();
        biayaTotal = getBiayaTotal();
    }
    // fungsi untuk menghitung biaya layanan
    float getBiayaLayanan(){
        float total = 0;
        for(int i = 0;pesanan[i];i++)
            total += pesanan[i]->subtotal();
        return total * layanan->biaya;
    }
    // fungsi untuk menghitung total biaya int layanan, float subtotal
    float getBiayaTotal(){
        float total = 0;
        for(int i = 0;pesanan[i];i++)
            total += pesanan[i]->subtotal();
        return total + getBiayaLayanan();
    }
    // fungsi untuk print data pelanggan
    void printDataPelanggan(){
        cout << "Nomor Order\t\t: " << nomorOrder << "\n";
        cout << "Nama Pelanggan\t\t: " << nama << "\n";
        cout << "Layanan\t\t\t: " << layanan->nama << "\n";
        cout << "Tanggal Transaksi\t: " << timestamp;
        cout << "Pesanan yang dipesan\t: \n";
        traversalPesanan();
        printBatas();
        cout << "Subtotal\t\t: Rp " << fixed << setprecision(0) << biayaTotal - biayaLayanan << "\n";
        cout << "Biaya Layanan\t\t: Rp " << biayaLayanan << "\n";
        cout << "Total Biaya\t\t: Rp " << fixed << setprecision(0) << biayaTotal<< "\n";
    }
}pelanggan;

// fungsi untuk traversal laporan penjualan
void traversalReport(List<DataPelanggan> &listPelanggan){

    if (listPelanggan.empty()){
        cout << "Laporan penjualan kosong !\n";
        return;
    } 

    cout << "Nomor\tNo. Order\tNama Pelanggan\t\tLayanan\t\tTotal Biaya\n";
    for(int i=0;listPelanggan[i];i++){

        printBatas();
        cout << setw(8) << left << i+1 << setw(16) << left << listPelanggan[i]->nomorOrder
                << setw(24) << left << listPelanggan[i]->nama << setw(16) << left <<  listPelanggan[i]->layanan->nama
                << "Rp "<< fixed << setprecision(0) << setw(6) << left <<  listPelanggan[i]->biayaTotal << "\n";
    }
}

// DEFINISI FUNGSI
void _inisialisasiMenuPreset(){
    for(int i = 0;i<10;i++)
    menuPesananCoffeeShop += PRESET_PESANAN[i];
}
void printMenu(){
    cout << "No. " << setw(22) << left << "Nama Pesanan" << setw(2) << left << "Stok\t   "<< "Harga\n";
    printBatas();
    for (int i=0;menuPesananCoffeeShop[i]; i++){
        cout << setw(4) << left << i+1 << setw(22) << left << menuPesananCoffeeShop[i]->nama << setw(2) <<  menuPesananCoffeeShop[i]->stok 
                << " pcs " << "  Rp " <<  menuPesananCoffeeShop[i]->harga << "\n";
    }   
    printBatas();
}
string getTime(){
    time_t curr_time;
    curr_time = time(0);
    return ctime(&curr_time);
}