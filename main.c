#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_LINES 100

// Yapı tanımlaması
typedef struct {
    char isim[50];
    char soyisim[50];
    float satis;
    float fark; // Performans farkı
} Kisi;

// Karşılaştırma fonksiyonu (önce isim, sonra soyisim)
int compare(const void *a, const void *b) {
    Kisi *kisiA = (Kisi *)a;
    Kisi *kisiB = (Kisi *)b;
    int isimCompare = strcmp(kisiA->isim, kisiB->isim);
    if (isimCompare == 0) {
        return strcmp(kisiA->soyisim, kisiB->soyisim);
    }
    return isimCompare;
}

int main() {
    FILE *file = fopen("C:/Users/enese/CLionProjects/donem_sonu/satis.txt", "r");
    if (!file) {
        printf("Dosya açılamadı!\n");
        return 1;
    }

    Kisi kisiler[MAX_LINES];
    int count = 0;
    char line[MAX_LINE_LENGTH];

    // Dosyayı satır satır oku
    while (fgets(line, sizeof(line), file)) {
        // Soyisim-isim formatını isim-soyisim formatına çevir
        sscanf(line, "%s %s %f", kisiler[count].soyisim, kisiler[count].isim, &kisiler[count].satis);
        count++;
    }
    fclose(file);

    // En yüksek satış değerini bul
    float maxSatis = 0.0;
    for (int i = 0; i < count; i++) {
        if (kisiler[i].satis > maxSatis) {
            maxSatis = kisiler[i].satis;
        }
    }

    // Performans farkını hesapla
    for (int i = 0; i < count; i++) {
        kisiler[i].fark = maxSatis - kisiler[i].satis;
    }

    // Alfabetik sıraya göre sırala (önce isim, sonra soyisim)
    qsort(kisiler, count, sizeof(Kisi), compare);

    // Performans verilerini dosyaya yaz
    FILE *outFile = fopen("C:/Users/enese/CLionProjects/donem_sonu/prfrmns.txt", "w");
    if (!outFile) {
        printf("Çıktı dosyası açılamadı!\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(outFile, "%s %s %.2f\n", kisiler[i].isim, kisiler[i].soyisim, kisiler[i].fark);
    }
    fclose(outFile);

    printf("Performans verileri 'prfrmns.txt' dosyasına yazıldı.\n");
    return 0;
}
