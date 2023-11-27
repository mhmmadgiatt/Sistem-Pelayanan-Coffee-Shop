// file header untuk fungsi menu utama

// fungsi untuk menampilkan menu utama
    void display(){
        int select = 0;
        while(true){
            system("cls");
            printBatas();
            cout << "\t\t\t   SISTEM PELAYANAN COFFEE SHOP\n";
            printBatas();
            cout << "\t\t\t\t  Menu Utama\n";
            cout << "1. Antrian Pesanan\n"
                 << "2. Proses Pesanan\n"
                 << "3. Checkout\n"
                 << "4. Laporan Penjualan\n"
                 << "5. Exit Program\n";
            printBatas();
            cout << "Masukkan pilihan (1-5) : "; 
            cin >> select;

            switch(select){
                case 1:
                    menuAntrian();
                    break;
                case 2:
                    menuProses();
                    break;
                case 3:
                    menuCheckout();
                    break;
                case 4:
                    menuReport();
                    break;            
                case 5:
                    dealloc();
                    cout << "Program selesai !";
                    exit(0);
                    break;
                default:
                    if (cin.fail()){
                        fail();
                    }
                    cout << "Input salah !\n";
            }
            system("pause");
        }
    }