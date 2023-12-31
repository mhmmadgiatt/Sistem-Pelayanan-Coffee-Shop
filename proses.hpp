// file header untuk memproses pesanan pada antrian

// fungsi untuk memproses pesanan berdasarkan prioritas
void menuProses(){
    system("cls");
    printBatas();
    cout << "\t\t\t   SISTEM PELAYANAN COFFEE SHOP\n";
    printBatas();
    cout << "\t\t\t      Menu Proses Pesanan\n";

    if (queuePelanggan.empty()){
    cout << "Antrian kosong !\n";
    }
    else {
        DataPelanggan *pHelp = queuePelanggan.head;
        pushDeleteAction(pHelp,&queuePelanggan);
        queuePelanggan.dequeue(pHelp);
        queueCheckout.enqueue(pHelp);
        pushAddAction(pHelp,&queueCheckout,2);
        printBatas();
        pHelp->printDataPelanggan();
        printBatas();
        cout << "Pesanan dengan No. Order : " << pHelp->nomorOrder <<
                " telah diproses !\n"
                "Harap segera lakukan checkout pesanan !\n";
    }
}