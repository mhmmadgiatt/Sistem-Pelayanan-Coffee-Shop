// file header untuk fungsi antrian pesanan

// fungsi untuk traversal antrian
void traversalAntrian(){
    if (queuePelanggan.head == nullptr){
        cout << "Antrian kosong !\n";
    } else {
        system("cls");
        printBatas();
        cout << "\t\t\t   SISTEM PELAYANAN COFFE SHOP\n";
        printBatas();
        cout << "\t\t\t      Menu Antrian Pesanan\n";
        for(int count = 0;queuePelanggan[count];count++) {
            printBatas();
            cout << "Antrian ke-" << count+1 << "\n";
            printBatas();
            queuePelanggan[count]->printDataPelanggan();
        }
    }
}

// fungsi untuk melihat detail pesanan 
void detailPesanan(){
    int nomorOrder;
    int flag = 0;
    while (true){
        cout << "Masukkan nomor order : ";
        cin >> nomorOrder;
        if (!cin.fail() && nomorOrder > 0){
            break;
        }
        fail();
        cout << "Input salah !\n";        
    }
    if (queuePelanggan.empty()){
        system("cls");
        printBatas();
        cout << "\t\t\t   SISTEM PELAYANAN COFFEE SHOP\n";
        printBatas();
        cout << "\t\t\t      Menu Detail Pesanan\n";
        cout << "Antrian kosong !\n";
    }
    else {
        for(int i = 0;queuePelanggan[i];i++){
            if (queuePelanggan[i]->nomorOrder == nomorOrder){
                flag = 1;
                system("cls");
                printBatas();
                cout << "\t\t\t   SISTEM PELAYANAN COFFEE SHOP\n";
                printBatas();
                cout << "\t\t\t      Menu Detail Pesanan\n";
                queuePelanggan[i]->printDataPelanggan();
                printBatas();
                break;
            }
        }
        if (flag == 0){
            cout << "Nomor order tidak tersedia !\n";
        }
    }
}

void hapusPesanan(){
    int nomorOrder;
    int flag = 0;
    while (true){
        cout << "Masukkan nomor order : ";
        cin >> nomorOrder;
        if (!cin.fail() && nomorOrder > 0){
            break;
        }
        fail();
        cout << "Input salah !\n";        
    }
    if (queuePelanggan.empty()){
        system("cls");
        printBatas();
        cout << "\t\t\t   SISTEM PELAYANAN COFFEE SHOP\n";
        printBatas();
        cout << "\t\t\t      Menu Hapus Pesanan\n";
        cout << "Antrian kosong !\n";
    }
    else {
        for(int i = 0;queuePelanggan[i];i++){
            if (queuePelanggan[i]->nomorOrder == nomorOrder){
                flag = 1;
                system("cls");
                printBatas();
                cout << "\t\t\t   SISTEM COFFEE SHOP\n";
                printBatas();
                cout << "\t\t\t      Menu Hapus Pesanan\n";
                queuePelanggan[i]->hapus();
                printBatas();
                break;
            }
        }
        if (flag == 0){
            cout << "Nomor order tidak tersedia !\n";
        }
    }
}

// fungsi untuk menu antrian pesanan
void menuAntrian(){
    system("cls");
    printBatas();
        cout << "\t\t\t   SISTEM PELAYANAN COFFEE SHOP\n";
        printBatas();
        cout << "\t\t\t      Menu Antrian Pesanan\n"
            "1. Tambah Pesanan\n"
            "2. Lihat Antrian\n"
            "3. Cetak Detail Pesanan\n"
            "4. Hapus Antrian\n";
            printBatas();
    int select;           
    cout << "Masukkan pilihan (1-4) : ";
    cin >> select;
    printBatas();
    
    switch (select){
        case 1:{
            DataPelanggan *newPelanggan = new DataPelanggan;
            newPelanggan->insertDataPelanggan();
            queuePelanggan.priority_enqueue(newPelanggan);
            pushAddAction(newPelanggan, &queuePelanggan, 11);
            for(int i = 0;newPelanggan->pesanan[i];i++){
                auto &stok = (newPelanggan->pesanan[i]->pesanan->stok);
                auto quantity = (newPelanggan->pesanan[i]->quantity);
                pushEditAction(&stok, stok - quantity, 2);
                stok -= quantity;
            }
            break;}
        case 2:
            traversalAntrian();
            break;
        case 3:
            detailPesanan();
            break;
        case 4:
            hapusPesanan();
            break;
        default:
            if (cin.fail()){
                fail();
            }
            cout << "Input salah !\n";
    }
}
