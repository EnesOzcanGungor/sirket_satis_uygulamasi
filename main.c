#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SATIR_UZUNLUGU 100
#define MAX_SATIR 12

// Yapı tanımlaması
typedef struct {
    char isim[20];
    char soyisim[20];
    float satis;
    float fark; // Performans farkı
} Kisi;

int karsilastir(const void *a, const void *b); // fonksiyon prototipi kullaniyoruz.

int main() {
    FILE *file = fopen("satis.txt", "r");
    if (!file) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    Kisi kisiler[MAX_SATIR];
    int sayac = 0;
    char line[SATIR_UZUNLUGU];

    // Dosyayı satır satır oku
    while (fgets(line, sizeof(line), file)) {
        // Soyisim-isim formatını isim-soyisim formatına çevir
        sscanf(line, "%s %s %f", kisiler[sayac].soyisim, kisiler[sayac].isim, &kisiler[sayac].satis); // burada direkt soyisim, isim olarak aldigimiz icin cikti dosyasina yazarken
                                                                                                      // ekstra islem yapmadan isim,soyisim seklinde yazabiliriz.
        sayac++;
    }
    fclose(file);

    // En yüksek satış değerini bul
    float maxSatis = 0.0;
    for (int i = 0; i < sayac; i++) {
        if (kisiler[i].satis > maxSatis) {
            maxSatis = kisiler[i].satis;
        }
    }

    // Performans farkını hesapla
    for (int i = 0; i < sayac; i++) {
        kisiler[i].fark = maxSatis - kisiler[i].satis;
    }

    // Alfabetik sıraya göre sırala
    qsort(kisiler, sayac, sizeof(Kisi), karsilastir); // burada karsilastir fonksiyonunu quick sort algoritmasiyla stringlere uyguluyoruz.

    // Performans verilerini dosyaya yaz
    FILE *outFile = fopen("prfrmns.txt", "w");
    if (!outFile) { // dosyanin acilip acilmadigini kontrol et, acilmadiysa uyari metnini yaz.
        printf("Cikti dosyasi acilamadi!\n");
        return 1;
    }

    for (int i = 0; i < sayac; i++) { // dosya acildiysa verileri dosyaya yaz.
        fprintf(outFile, "%s %s %.2f\n", kisiler[i].isim, kisiler[i].soyisim, kisiler[i].fark); //
    }
    fclose(outFile); // dosyayi kapat

    printf("Performans verileri 'prfrmns.txt' dosyasina yazildi.\n");
    return 0;
}

// karsilastir fonksiyonu
int karsilastir(const void *a, const void *b) {
    Kisi *kisiA = (Kisi *)a;
    Kisi *kisiB = (Kisi *)b;
    int isimkarsilastir = strcmp(kisiA->isim, kisiB->isim);
    if (isimkarsilastir == 0) {
        return strcmp(kisiA->soyisim, kisiB->soyisim);
    }
    return isimkarsilastir;
}
