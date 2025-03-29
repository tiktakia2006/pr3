# ПРАКТИЧНА РОБОТА 3

## ЗАВДАННЯ 1

## Умова
Запустіть Docker-контейнер і поекспериментуйте з максимальним лімітом ресурсів відкритих файлів. Для цього виконайте команди у вказаному порядку:
$ ulimit -n
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3001
$ ulimit -n 2000
$ ulimit -n
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3000

Як наступне вправу, повторіть перераховані команди з root-правами.


## Код до завдання
ulimit -n
ulimit -aS | grep  "open files";
ulimit -aH | grep  "open files";
ulimit -n 3000
ulimit -aS | grep  "open files";
ulimit -aH | grep  "open files";

## Опис програми
Завдання полягає в тому, щоб перевірити та змінити ліміт відкритих файлів у системі за допомогою команди ulimit.
Спочатку ми дивимося поточні налаштування, змінюємо ліміт на 3000 і перевіряємо зміни. Потім повторюємо ці дії з правами root для порівняння.

## Результат програми
![image](https://github.com/user-attachments/assets/2fff0f4f-d915-45d0-acd3-aefc0f0f460e)


## ЗАВДАННЯ 2

## Умова
У Docker-контейнері встановіть утиліту perf(1). Поекспериментуйте з досягненням процесом встановленого ліміту.

## Код до завдання
```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int i = 0;
    int max_files = 5000;
    int fds[max_files];

    for (i = 0; i < max_files; i++) {
        fds[i] = open("tempfile.txt", O_CREAT | O_WRONLY, 0666);
        if (fds[i] < 0) {
            perror("Failed to open file");
            break;
        }
    }

    printf("Opened %d files successfully.\n", i);

    for (int j = 0; j < i; j++) {
        close(fds[j]);
    }

    return 0;
}
```

## Опис програми
Програма намагатиметься відкрити 5000 файлів і виведе кількість відкритих
файлів, яку їй вдалося відкрити.
Якщо ліміт досягнуто, програма виведе помилку і припинить виконання.
У моєму випадку, ми намагаємось використовувати утиліту perf, щоб
моніторити процеси при досягненні ліміту. Проблема з установкою perf у
моєму контейнері виникає через те, що Docker-контейнер може не мати доступу
до всіх необхідних пакетів або модулів ядра для роботи perf, особливо у
випадку з WSL2, де можуть бути обмеження на доступ до функцій ядра.
Саме тому я написав програму для прикладу, бо perf не можу використовувати.
Моя програма імітує перевищення ліміту ресурсів, такого як максимальна
кількість відкритих файлів(1997 із 5000 файлів відкрито). Це дає змогу
зрозуміти, як система поводиться, коли процеси намагаються використовувати
більше ресурсів, ніж дозволено. Замість утиліти perf я експериментую з
лімітами безпосередньо через команду ulimit для обмеження кількості
відкритих файлів і спостерігаю, як програма реагує на ці обмеження. Так,
програма демонструє, як система відмовляється або дає помилки при спробі
перевищити встановлені ліміти.

## Результат програми
![image](https://github.com/user-attachments/assets/c9466594-16d0-4121-8681-bab1d2ee2fab)


## ЗАВДАННЯ 3

## Умова
Напишіть програму, що імітує кидання шестигранного кубика.
Імітуйте кидки, результати записуйте у файл, для якого попередньо встановлено обмеження
на його максимальний розмір (max file size). Коректно обробіть ситуацію перевищення ліміту.

## Код до завдання
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_SIZE 100

int main() {
    FILE *file = fopen("dice_rolls.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int roll;
    srand(time(NULL));

    for (int i = 0; i < 1000; i++) {
        roll = (rand() % 6) + 1;

        fseek(file, 0, SEEK_END);
        if (ftell(file) >= MAX_FILE_SIZE) {
            printf("File size limit reached\n");
            fclose(file);
            return 0;
        }

        fprintf(file, "%d\n", roll);
    }

    printf("Data successfully written to file\n");

    fclose(file);
    return 0;
}
```

## Опис програми
Програма імітує кидання шестигранного кубика.
Вона генерує випадкові числа від 1 до 6, які відповідають результатам кидків. Ці числа записуються у файл dice_rolls.txt,
при цьому програма перевіряє, чи не перевищено максимальний розмір файлу (100 байт). Якщо файл досягне ліміту, програма
виводить повідомлення про досягнення ліміту і завершується. Якщо ж файл не досягає цього ліміту, то дані успішно записуються в файл,
і після завершення кидків виводиться повідомлення про успішне завершення процесу.

## Результат програми
![image](https://github.com/user-attachments/assets/ac311ddd-5d42-439b-8481-adce3e364300)
![image](https://github.com/user-attachments/assets/c66ee97e-1205-405a-80d2-2277ef796ecb)



## ЗАВДАННЯ 4

## Умова
Напишіть програму, що імітує лотерею, вибираючи 7 різних цілих чисел у діапазоні від 1 до 49 і ще 6 з 36.
Встановіть обмеження на час ЦП (max CPU time) і генеруйте результати вибору чисел (7 із 49, 6 із 36). Обробіть ситуацію, коли ліміт ресурсу вичерпано.

## Код до завдання
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>

#define MAX_CPU_TIME 5

void set_cpu_time_limit() {
    struct rlimit rl;
    rl.rlim_cur = rl.rlim_max = MAX_CPU_TIME;
    if (setrlimit(RLIMIT_CPU, &rl) == -1) {
        perror("Failed to set CPU time limit");
        exit(1);
    }
}

void generate_lottery_numbers() {
    int i, num;
    int numbers_49[49], numbers_36[36];
    int selected_49[7], selected_36[6];

    for (i = 0; i < 49; i++) numbers_49[i] = i + 1;
    for (i = 0; i < 36; i++) numbers_36[i] = i + 1;

    for (i = 0; i < 7; i++) {
        num = rand() % (49 - i);
        selected_49[i] = numbers_49[num];
        numbers_49[num] = numbers_49[49 - i - 1];
    }

    for (i = 0; i < 6; i++) {
        num = rand() % (36 - i);
        selected_36[i] = numbers_36[num];
        numbers_36[num] = numbers_36[36 - i - 1];
    }

    printf("7 numbers from 49: ");
    for (i = 0; i < 7; i++) printf("%d ", selected_49[i]);
    printf("\n6 numbers from 36: ");
    for (i = 0; i < 6; i++) printf("%d ", selected_36[i]);
    printf("\n");
}

int main() {
    set_cpu_time_limit();
    srand(time(NULL));

    generate_lottery_numbers();
    return 0;
}
```

## Опис програми
Програма імітує лотерею, випадково вибираючи сім різних чисел із сорока дев’яти та шість із тридцяти шести.
Перед цим вона встановлює обмеження на використання процесорного часу до п’яти секунд, щоб уникнути перевантаження системи.
Спочатку створюються масиви з числами від одного до сорока дев’яти та від одного до тридцяти шести. 
Потім за допомогою алгоритму вибору без повторень програма випадково визначає сім і шість чисел відповідно. 
Отримані результати виводяться на екран.

Якщо програма перевищить ліміт процесорного часу, вона аварійно завершить роботу.

## Результат програми
![image](https://github.com/user-attachments/assets/bf97107e-b2b5-4d7b-84a8-c02a4f665157)




## ЗАВДАННЯ 5

## Умова
Напишіть програму для копіювання одного іменованого файлу в інший. Імена файлів передаються у вигляді аргументів.
Програма має:
перевіряти, чи передано два аргументи, інакше виводити "Program need two arguments";
перевіряти доступність першого файлу для читання, інакше виводити "Cannot open file .... for reading";
перевіряти доступність другого файлу для запису, інакше виводити "Cannot open file .... for writing";
обробляти ситуацію перевищення обмеження на розмір файлу.

## Код до завдання
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1 MB

void check_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    if (ftell(file) > MAX_FILE_SIZE) {
        printf("File size limit exceeded\n");
        exit(1);
    }
    fseek(file, 0, SEEK_SET);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    FILE *dst = fopen(argv[2], "w");
    if (!dst) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(src);
        return 1;
    }

    check_file_size(src);

    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);

    return 0;
}
```

## Опис програми
Програма копіює вміст одного файлу в інший. Вона приймає два аргументи — імена файлів. 
Якщо аргументів менше або більше, виводить повідомлення про помилку. Далі перевіряє, 
чи можна відкрити вихідний файл для читання, і якщо ні — повідомляє про це. Потім перевіряє, 
чи можна відкрити цільовий файл для запису. Перед копіюванням програма перевіряє розмір вихідного файлу, 
і якщо він перевищує 1 МБ, зупиняє роботу. Якщо все добре, по черзі читає символи з вихідного файлу і записує їх у цільовий. 
Завершує роботу, закриваючи файли

## Результат програми
![image](https://github.com/user-attachments/assets/4af747bb-cdba-4e8d-8d84-67c143878a95)
![image](https://github.com/user-attachments/assets/2a63005c-3dbf-4513-a52f-fcfc846bf1bb)
![image](https://github.com/user-attachments/assets/1b958e48-1c6e-4a09-87d0-18844c46c972)


## ЗАВДАННЯ 6

## Умова
Напишіть програму, що демонструє використання обмеження (max stack segment size). Підказка: рекурсивна програма активно використовує стек.

## Код до завдання
```c
#include <stdio.h>

void recursiveFunction(int n) {
    if (n == 0) {
        return;
    }
    printf("Recursive call: %d\n", n);
    recursiveFunction(n - 1);
}

int main() {
    int depth = 10000;
    printf("Start of recursion\n");
    recursiveFunction(depth);
    return 0;
}
```

## Опис програми
Ця програма ілюструє обмеження розміру стекового сегмента, використовуючи глибоку рекурсію. 
У функції recursiveFunction кожен виклик зменшує n на одиницю, поки не досягне нуля. У main задається 
велика глибина рекурсії — 10000. Це може призвести до переповнення стека, якщо дозволений розмір стеку 
недостатній. Таким чином, програма демонструє, як рекурсія витрачає стекову пам’ять і може спричинити помилку, 
якщо глибина занадто велика

## Результат програми
![image](https://github.com/user-attachments/assets/fd38431a-05c2-4d10-b105-7d78a3259124)
![image](https://github.com/user-attachments/assets/4ca946a3-96e0-4caf-a921-250edb8cbf94)


## ЗАВДАННЯ 7 (ВАРІАНТ 13)

## Умова
Дослідити зміну обмежень ресурсів через /etc/security/limits.conf

## Код до завдання
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit limit;

    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Soft limit for open files: %ld\n", limit.rlim_cur);
        printf("Hard limit for open files: %ld\n", limit.rlim_max);
    } else {
        perror("getrlimit for RLIMIT_NOFILE");
    }

    if (getrlimit(RLIMIT_NPROC, &limit) == 0) {
        printf("Soft limit for processes: %ld\n", limit.rlim_cur);
        printf("Hard limit for processes: %ld\n", limit.rlim_max);
    } else {
        perror("getrlimit for RLIMIT_NPROC");
    }

    return 0;
}
```

## Опис програми
Файл /etc/security/limits.conf у Linux використовується для налаштування
обмежень на використання системних ресурсів користувачами чи групами
користувачів. Зміни в цьому файлі дозволяють обмежити кількість відкритих
файлів, процесів, пам'яті та інші ресурси, що можуть бути використані певними
користувачами або групами. Це корисно для запобігання надмірного
використання ресурсів і стабільної роботи системи, особливо на серверах з
багатьма користувачами. Встановлення обмежень через limits.conf забезпечує
баланс між продуктивністю та безпекою системи.

## Результат програми
![image](https://github.com/user-attachments/assets/366d870d-e640-45e8-a766-5c8075aec3c6)
![image](https://github.com/user-attachments/assets/82f5977e-ca87-49a5-b5e6-f0f813bd5d1c)

Код успішно отримує поточні обмеження ресурсів для відкритих файлів і
процесів.
Вивід показує, що жорсткі (hard) ліміти значно вищі за м’які (soft), що означає
можливість їх збільшення.
Обмеження можна змінити через файл /etc/security/limits.conf, але для цього
потрібні відповідні права доступу.
Використання ulimit -a або getrlimit() у програмі дозволяє перевірити всі
активні обмеження.
Зміни в limits.conf можуть вимагати перезавантаження системи або повторного
входу користувача, щоб набрали чинності.

