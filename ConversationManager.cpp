#include "ConversationManager.h"
#include "DataManager.h"

ConversationManager::ConversationManager()
{
}

ConversationManager::ConversationManager(Array<Message>& privateMessagePool, Array<Message>& commonMessagePool)
{
    allUsers = UserManager(std::move(std::make_unique<Array<User>>(10)));
}

void ConversationManager::cleanConsole()         // Очищаем консоль 
{
    system("cls");
}

void ConversationManager::start()
{
    this->greeting();
    bool isItNextLoop = false;
    int uNum{ -1 };
    //Начальное меню
    while (true)
    {
        char choice = this->regOrComm();
        switch (choice)
        {
        case '1':
            if (isItNextLoop)
            {
                this->cleanConsole();
            }
            isItNextLoop = true;
            this->userRegistration();
            break;
        case '2':
            if (isItNextLoop)
            {
                this->cleanConsole();
                isItNextLoop = true;
            }
            else
            {
                std::cout << "\n\nНет зарегистрированных пользователей, начните с п.1.\n\n";
                break;
            }
            uNum = this->usersInput();		//номер зарегистрировавшегося пользователя из массива Users
            if (uNum > -1)
            {
                User user = allUsers.getUser(uNum);			//получаем запись этого пользователя
                this->userMessChoise(user);
            }
            break;
        case '3':
            std::cout << "\n\nРабота программы завершена.\n";
            return;
        }
    }
    for (int i = 0; i < ptrPrivCharts.getCount(); ++i)
    {
        delete ptrPrivCharts[i];
    }
}

void ConversationManager::greeting()
{
    this->cleanConsole();
    std::cout << "Приветствую!!\n\n";
}

char ConversationManager::regOrComm()
{
    char sim;
    std::cout << "Выберите один из возможных режимов программы:\n1 - Регистрация нового пользователя.\n2 - Вход зарегистрированного пользователя.\n3 - Завершить работу программы.\nВведите номер планируемого действия: ";
    while (true)
    {
        sim = _getch();

        if (sim == '1' or sim == '2' or sim == '3')
        {
            std::cout << sim << std::endl << std::endl;
            return sim;
        }
    }
}

bool ConversationManager::userRegistration()
{
    this->cleanConsole();
    std::cout << "\n\nРегистрация нового пользователя:\n\n";
    bool isSpellingBad = true;
    std::string log{ "" };
    std::string name{ "" };
    std::string pass{ "" };

    while (isSpellingBad)
    {
        std::cout << "Для выхода из режима регистрации, введите '!' и 'ENTER'.\n";
        std::cout << "Логин (латинские буквы, цифры и знак нижнего подчёркивания): ";
        getline(std::cin, log);
        if (log.length() == 0)
        {
            std::cout << "\n\nПустая строка не может быть логином! Вышли из режима Регистрации нового пользователя.\n\n";
            return false;
        }
        if (log.length() == 1 && log[0] == '!')         // выход на верхний уровень
        {
            this->cleanConsole();
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : log)                             // контроль правильности введенных символов
        {
            if (!((c <= 57 && c >= 48) ||                     // символ - цифра
                (c <= 90 && c >= 65) ||                     // символ заглавная латинская буква
                (c <= 122 && c >= 97) ||                     // символ прописная латинская буква
                (c == 95)))                                  // символ нижнее подчеркивание
            {
                std::cout << "К сожалению, в логине нашлись недопустимые символы. \nПопытайтесь ввести логин заново.\n\n";
                isSimbolBad = true;
                break;
            }
        }
        if (!isSimbolBad)                               //Все символы правильные, проверяем на уникальность логина
        {
            bool isLogUnique = true;
            for (int i = 0; i < allUsers.getCount(); ++i)
            {
                if (allUsers.findUserByLogin(std::move(log)))
                {
                    isLogUnique = false;
                    break;
                }
            }
            if (isLogUnique)
                isSpellingBad = false;
            else
            {
                std::cout << "Такой логин уже зарегистрирован.\nВведите новый логин: ";
            }
        }
    }
    //std::cout << "Введен логин: " << log << std::endl;

    isSpellingBad = true;
    while (isSpellingBad)
    {
        std::cout << "Имя (русские буквы, цифры и знак нижнего подчёркивания): ";
        getline(std::cin, name);
        //std::cout << name[0] << (int)name[0] << std::endl;        // тестирование букв и цифр
        if (name.length() == 0)
        {
            std::cout << "\n\nПустая строка не может быть имененм пользователя. Вышли из режима регистрации пользователя.\n\n";
            return false;
        }
        if (name.length() == 1 && name[0] == '!')         // выход на верхний уровень
        {
            std::cout << "\n\nРегистрация нового пользователя была прервана.\n\n";
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : name)                             // контроль правильности введенных символов
        {
            if (!((c <= 57 && c >= 48) ||                     // символ - цифра
                (c <= -38 && c >= -64) ||                     // символ русская буква А-Ъ
                (c <= -6 && c >= -36) ||                     // символ русская буква Ь-ъ
                (c <= -1 && c >= -4) ||                     // символ русская буква ь-я
                c == -88 || c == -72 ||                     // символы Ё, ё
                c == -5 || c == -37 ||                     // символы ы, Ы
                (c == 95)))                                   // символ нижнее подчеркивание
            {
                /*      ***Отладка***
                for (auto& c1 : name)
                {
                    std::cout << c1 << "\t" << (int)c1 << std::endl;
                }
                */
                std::cout << "К сожалению, в имени нашлись недопустимые символы. \nПопробуйте ввести еще раз.\n\n";
                isSimbolBad = true;
                break;
            }
        }
        if (!isSimbolBad)                               //Все символы правильные, проверяем на уникальность логина
        {
            bool isLogUnique = true;
            for (int i = 0; i < allUsers.getCount(); ++i)
            {
                if (allUsers.findUserByNickname(std::move(name)))
                {
                    isLogUnique = false;
                    break;
                }
            }
            if (isLogUnique)
                isSpellingBad = false;
            else
            {
                std::cout << "Пользователь с таким имененм уже есть.\nВведите новое имя пользователя: ";
            }
        }
    }
    //std::cout << "Введено имя: " << name << std::endl;                                            //***Отладка****

    while (true)
    {
        pass = "";
        std::cout << "Пароль (латинские буквы, цифры и \nспециальные знаки, кроме пробела и восклицательного знака): ";
        char c;

        while ((c = _getch()) != '\r')
        {
            pass.push_back(c);
            _putch('*');
        }
        //std::cout << "\nСчитанный пароль: "<< pass << std::endl;                                 //***Отладка****

        if (pass.length() == 1 && pass[0] == '!')         // выход на верхний уровень
        {
            std::cout << "\n\nРегистрация нового пользователя была прервана.\n\n";
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : pass)                             // контроль правильности введенных символов
        {
            if (!(c <= 126 && c >= 34) or c == '!' or c == ' ')                  // Все печатные символы первой страницы ASCII кроме ! и пробела
            {
                std::cout << "\nБудьте внимательны! При наборе пароля допущена ошибка.\nПопытайтесь ввести пароль заново: ";
                isSimbolBad = true;
                //std::cin.ignore(32767, '\n'); // удаляем лишние значения
                break;
            }

        }
        if (!isSimbolBad)
            //isSpellingBad = false;
            break;
    }
    //std::cout << "Введен пароль: " << pass << std::endl;                                          //***Отладка****
    //Заносим в массив нового пользователя
    std::cout << "\n\n";
    allUsers.addUser(std::move(User(log, name, pass)));
    std::cout << "\n";
    //std::cout << "\n\nНовый пользователь '" << name << "' успешно зарегистрирован.\n\n";
    return true;
}

int ConversationManager::usersInput()
{
    std::string log{ "" };
    std::string pass{ "" };
    bool isLogGood = false;
    bool isPassGood = false;
    this->cleanConsole();
    std::cout << "\n\nВход пользователя.\n\n";
    std::cout << "\n\nВведите логин или символ '!' для возврата: ";
    getline(std::cin, log);
    if (log.length() == 1 && log == "!")
    {
        std::cout << "\n\nВерификация пользователя была прервана.\n\n";
        return -1;
    }
    //перебираем массив пользователей на совпадение логина
    int userNum{ -1 };

    if (!allUsers.findUserByLogin(std::move(log), userNum))      //Введенный логин не найден
    {
        std::cout << "\n\nОшибка при вводе логина пользователя!\n\n";
        return -1;
    }

    std::cout << "\n\nВведите пароль: ";

    char c;
    while ((c = _getch()) != '\r')
    {
        pass.push_back(c);
        _putch('*');
    }
    // сравниваем пароль с данными пользователя из массива
    if (pass != allUsers.getUser(userNum).getPassword())        //пароль не совпал
    {
        std::cout << "\n\nОшибка при вводе пароля пользователя.\n\n";
        userNum = -1;
    }

    return userNum;
}

void ConversationManager::userMessChoise(User& user)
{
    bool isRun = true;
    //Имя пользователя
    std::string name = user.getNickname();
    while (isRun)
    {
        this->cleanConsole();
        std::cout << "\n\n" << user.getNickname() << ", возможные действия:\n";
        std::cout << "Выберите:\n1 - Перейти в общий чат.\n2 - Перейти к личным чатам.\n";

        //std::cout << "4 - просмотреть частные сообщения (количество сообщений: " << "countPM" << ").\n";
        std::cout << "3 - завершить работу с сообщениями.\n";
        std::cout << "\nРезультат выбора : ";

        // отслеживаем выбор пользователя
        char sim;
        while (true)
        {
            sim = _getch();

            if (sim == '1' || sim == '2' || sim == '3')
            {
                std::cout << sim << std::endl << std::endl;
                break;
            }
        }

        if (sim == '1')  //перейти в общий чат
        {
            outputCommonMessage(); //вывод сообщений из общего чата

            std::cout << "\n\nХотите написать сообщение в общий чат?\nЦифра 1- Да, цифра 2 - Выйти из общего чата.: ";
            char sim;
            while (true)
            {
                sim = _getch();

                if (sim == '1' || sim == '2')
                {
                    std::cout << sim << std::endl << std::endl;
                    break;
                }
            }
            if (sim == '1')
            {

                inputCommonMessage(name);
            }
        }
        if (sim == '2')     //перейти к личным сообщениям
        {
            privateMesMenu(name);
        }
        if (sim == '3')         //завершить работу с сообщениями
            isRun = false;
    }
}

void ConversationManager::outputPrivateMesage(User& user)
{
    {
        this->cleanConsole();
        std::cout << "\nЧат. Все личные сообщения:\n\n";
        for (int i = 0; i < privateMessagePool.getCount(); ++i)
        {
            if (*privateMessagePool[i].getSendTo() == user.getNickname())
                std::cout << *privateMessagePool[i].getSendFrom() << " написал: " << *privateMessagePool[i].getMessage() << std::endl;
        }
        std::cout << "\n\nНажмите на любую клавишу, что бы выйти из режима прочтения чата личных сообщений: ";
        char sim;
        sim = _getch();
    }
}

void ConversationManager::outputCommonMessage()
{
    this->cleanConsole();
    std::cout << "\nОбщий чат. Все сообщения:\n\n";
    for (int i = 0; i < commonMessagePool.getCount(); ++i)
    {
        std::cout << "'" << *commonMessagePool[i].getSendFrom() << "'" << " написал: " << *commonMessagePool[i].getMessage() << std::endl;
    }
}

void ConversationManager::inputPrivateMessage(User& user)
{
    this->cleanConsole();
    std::cout << "\n\nВыберите номер пользователя, что бы написать сообщение: \n";
    int count = 0;
    for (int i = 0; i < allUsers.getCount(); ++i)
    {
        if (!(allUsers.getUser(i) == user))
        {
            std::cout << count << ". " << allUsers.getUser(i).getNickname() << std::endl;
            count++;
        }
    }
    int choise{ 0 };
    while (true)
    {
        choise = getIntValue();
        if (choise >= 0 && choise < count)   //выбрано правильное число
            break;
        else
        {
            std::cout << "\n\nНе удалось понять, какому пользователю Вы хотите написать сообщение. Попробуйте снова:";
        }
    }

    int index;
    allUsers.findUser(std::move(user), index);
    if (choise >= index) choise++;
    std::cout << "\nНаберите текст сообщение для " << allUsers.getUser(choise).getNickname() << ": ";
    std::string privateMes{ "" };
    getline(std::cin, privateMes);
    int mesNum = privateMessagePool.getCount();

    Message* ptrPrivateMes = new Message(mesNum, privateMes, user.getNickname(), allUsers.getUser(choise).getNickname());
    std::cout << "\n\nСообщение сохранено под номером: " << mesNum << " \n\n";
    privateMessagePool.add(std::move(*ptrPrivateMes));
    delete ptrPrivateMes;
}

void ConversationManager::inputCommonMessage(std::string& name)
{
    this->cleanConsole();
    std::cout << "\n\nНаберите сообщение для всех: ";
    std::string mes{ "" };
    getline(std::cin, mes);
    int mesNum = commonMessagePool.getCount();
    Message* ptrCommonMes = new Message(mesNum, mes, name);
    std::cout << "\n\nСообщение сохранено под номером: " << mesNum << " \n\n";
    commonMessagePool.add(std::move(*ptrCommonMes));
    delete ptrCommonMes;
}

int ConversationManager::amountPrivateMessage(std::string& name)
{
    int countPM{ 0 };
    for (int i = 0; i < privateMessagePool.getCount(); ++i)
    {
        if (*privateMessagePool[i].getSendTo() == name)
        {
            countPM += 1;
        }
    }
    return countPM;
}
void ConversationManager::privateMesMenu(std::string& name)
{
    int mainID = allUsers.getPosNumber(name);
    //Всех юзеров делим на два массива: с кем есть чаты и скем нет
    Array<int> haveChat;
    Array <int> noChart;
    for (int i = 0; i < ptrPrivCharts.getCount(); ++i)
    {
        if (ptrPrivCharts[i]->isItRightChat(mainID))
        {
            haveChat.add(ptrPrivCharts[i]->getAnotherUser(mainID));
        }
    }
    //haveChat.show();                            //отладка
    for (int i = 0; i < allUsers.getCount(); ++i)
    {
        bool hasUserInChat = false;
        for (int j = 0; j < haveChat.getCount(); ++j)
        {
            if (haveChat[j] == i)
            {
                hasUserInChat = true;
                break;
            }
        }
        std::cout << "i = " << i << hasUserInChat << std::endl;
        if (!hasUserInChat && (i != mainID))
            noChart.add(std::move(i));
    }
    //std::cout << "\n**************\n";
    //noChart.show();                         //отладка
    //printPrivateMessagePool();    
    //char pause;
    //pause = _getch();

    this->cleanConsole();
    if (haveChat.getCount() == 0)
    {
        std::cout << "\nПока у Вас не создано ни одного чата с пользователями:";
    }
    else
    {
        std::cout << "\n\n Имеющиеся чаты:";
        for (int i = 0; i < haveChat.getCount(); ++i)
        {
            int ii = haveChat[i];
            std::cout << std::endl << i << " : '" << allUsers.getUser(ii).getNickname() << "'";
            //std::cout << std::endl << i << " - " << allUsers.getUser(ii).getNickname() << "Кол - во не выведенных сообщений: ";
        }
    }

    if (haveChat.getCount() > 0)
        std::cout << "\n\nВыберите номер перед именем пользователя, чей чат Вы хотите открыть.";

    std::cout << " \n" << haveChat.getCount() << " : создать новый чат.\n";
    std::cout << haveChat.getCount() + 1 << " : выйти из меню.";

    //std::cout << "\n\nВаш выбор: ";
    int choise{ 0 };
    while (true)
    {
        choise = getIntValue();

        if (choise >= 0 && choise <= haveChat.getCount() + 1)   //выбрано правильное число
            break;
        else
        {
            std::cout << "\n\nНе удалось понять, что Вы хотели выбрать из списка. Попробуйте снова:";
        }
    }
    if (choise >= 0 && choise < haveChat.getCount())        //Прочитать и написать в в чат пользователю
    {
        readWritePrivateChat(mainID, haveChat[choise]);
    }
    else if (choise == haveChat.getCount())                 //создать новый чат
    {
        createNewChart(mainID, noChart);
    }
    else if (choise == haveChat.getCount() + 1)               //выйти на уровень вверх
    {
        return;
    }
}

void ConversationManager::readWritePrivateChat(int frstUserNum, int secndUserNum)
{
    //PrivateChat* a;
    int iConst{ 0 };
    // Цикл по чатам, ищем наш.
    for (int i = 0; i < ptrPrivCharts.getCount(); ++i)
    {
        //a = ptrPrivCharts[i];
        if (ptrPrivCharts[i]->isTwoUsersOk(frstUserNum, secndUserNum))          //нужный чат найден
        {
            iConst = i;
            break;
        }
    }
    Array<int> ar = ptrPrivCharts[iConst]->getArr();                                              //Вытащили массив с номерами чата
    std::cout << "\n\n";
    if (ar.getCount() > 0)
    {
        std::cout << "Чат:\n\n";
    }
    for (int i = 0; i < ar.getCount(); ++i)
    {
        int num = ar[i];
        std::string mes = *privateMessagePool.get(num).getMessage();
        std::string sender = *privateMessagePool.get(num).getSendFrom();
        std::cout << "'" << sender << "' написал:" << mes << std::endl;
    }
    std::cout << "\nЕсли хотите написать сообщение пользователю " << allUsers.getUser(secndUserNum).getNickname() << ", введите цифру 1, выйти из чата - 2: ";
    char sim;
    while (true)
    {
        sim = _getch();

        if (sim == '1' || sim == '2')
        {
            std::cout << sim << std::endl << std::endl;
            break;
        }
    }
    if (sim == '1')
    {
        std::cout << "\n\nСообщение: ";
        std::string mes{ "" };
        getline(std::cin, mes);
        int mesNum = privateMessagePool.getCount();
        std::string usName = allUsers.getUser(frstUserNum).getNickname();
        Message* ptrPrivateMes = new Message(mesNum, mes, usName);
        privateMessagePool.add(std::move(*ptrPrivateMes));
        delete ptrPrivateMes;

        ptrPrivCharts[iConst]->setMesNumber(mesNum);

    }
}

void ConversationManager::createNewChart(int mainID, Array<int>& noChart)
{
    if (noChart.getCount() > 0)
    {
        this->cleanConsole();
        std::cout << "\n\nПеречень имен пользователей, с которыми можно создать новый чат:";
        for (int i = 0; i < noChart.getCount(); ++i)
        {
            int a = noChart[i];
            std::cout << std::endl << i << " - '" << allUsers.getUser(a).getNickname() << "'";
        }
        std::cout << "\nВыберите номер пользователя или введите " << noChart.getCount() << " что бы выйти из меню: ";
        int choise{ 0 };
        while (true)
        {
            choise = getIntValue();
            if (choise >= 0 && choise <= noChart.getCount())   //выбрано правильное число
                break;
            else
            {
                std::cout << "\n\nНе удалось понять, что Вы хотели выбрать из списка. Попробуйте снова:";
            }
        }
        int a = noChart[choise];
        writeNewChart(mainID, a);
    }
    else
    {
        std::cout << "\n\nБольше не осталось пользователей, с которыми бы у Вас не было личного чата.";
        std::cout << "\nДля продолжения, нажмите любую клавишу.";
        char wait;
        wait = _getch();
        return;
    }
}

void ConversationManager::writeNewChart(int mainID, int otherUserNum)
{
    this->cleanConsole();

    std::cout << "\n\nДля создания нового чата, введите сообщение пользователю " << allUsers.getUser(otherUserNum).getNickname() << ".\n";
    std::cout << "Сообщение: ";
    std::string mes{ "" };
    getline(std::cin, mes);
    int mesNum = privateMessagePool.getCount();
    std::string usName = allUsers.getUser(mainID).getNickname();
    Message* ptrPrivateMes = new Message(mesNum, mes, usName);
    privateMessagePool.add(std::move(*ptrPrivateMes));
    delete ptrPrivateMes;
    PrivateChat* ptrCh = new PrivateChat(mainID, otherUserNum);     //забрали память !!!!!!!!!!!!!!!!!!!!!!!!!!
    ptrCh->setMesNumber(mesNum);
    ptrPrivCharts.add(std::move(ptrCh));
    ptrCh = nullptr;            //Предположительно, потеряли память  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void ConversationManager::printPrivateMessagePool()
{
    std::cout << "\nprivateMessagePool:\n";
    for (int i = 0; i < privateMessagePool.getCount(); ++i)
    {
        std::cout << "\nposition " << i << " : " << *privateMessagePool[i].getMessage() << "; Писатель: " << *privateMessagePool[i].getSendFrom();
    }

    std::cout << "\n\n ptrPrivCharts:\n";
    for (int i = 0; i < ptrPrivCharts.getCount(); ++i)
    {
        std::cout << "\nprivateChart " << i << " : ";
        PrivateChat* a = ptrPrivCharts[i];
        a->printAllPartners();
        Array<int> m = a->getArr();
        m.show();
    }
}

