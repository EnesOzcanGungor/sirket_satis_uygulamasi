#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define satir_uzunlugu 100
#define Max_satir 100

// Yapı tanımlaması
typedef struct {
    char isim[50];
    char soyisim[50];
    float satis;
    float fark; // Performans farkı
} Kisi;

// karsilastir fonksiyonu (önce isim, sonra soyisim)
int karsilastir(const void *a, const void *b) {
    Kisi *kisiA = (Kisi *)a;
    Kisi *kisiB = (Kisi *)b;
    int isimkarsilastir = strcmp(kisiA->isim, kisiB->isim);
    if (isimkarsilastir == 0) {
        return strcmp(kisiA->soyisim, kisiB->soyisim);
    }
    return isimkarsilastir;
}

int main() {
    FILE *file = fopen("C:/Users/enese/CLionProjects/donem_sonu/satis.txt", "r");
    if (!file) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    Kisi kisiler[Max_satir];
    int sayac = 0;
    char line[satir_uzunlugu];

    // Dosyayı satır satır oku
    while (fgets(line, sizeof(line), file)) {
        // Soyisim-isim formatını isim-soyisim formatına çevir
        sscanf(line, "%s %s %f", kisiler[sayac].soyisim, kisiler[sayac].isim, &kisiler[sayac].satis);
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

    // Alfabetik sıraya göre sırala (önce isim, sonra soyisim)
    qsort(kisiler, sayac, sizeof(Kisi), karsilastir);

    // Performans verilerini dosyaya yaz
    FILE *outFile = fopen("C:/Users/enese/CLionProjects/donem_sonu/prfrmns.txt", "w");
    if (!outFile) {
        printf("Cikti dosyasi acilamadi!\n");
        return 1;
    }

    for (int i = 0; i < sayac; i++) {
        fprintf(outFile, "%s %s %.2f\n", kisiler[i].isim, kisiler[i].soyisim, kisiler[i].fark);
    }
    fclose(outFile);

    printf("Performans verileri 'prfrmns.txt' dosyasina yazildi.\n");
    return 0;
}
