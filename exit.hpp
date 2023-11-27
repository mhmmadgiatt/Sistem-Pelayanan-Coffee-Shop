// file header untuk fungsi exit

// dealokasi memori seluruh pointer yang digunakan
void dealloc(){
    queuePelanggan.clear();
    queueCheckout.clear();
    salesReport.listPelanggan.clear();
    UndoStack.clear();
    RedoStack.clear();
}