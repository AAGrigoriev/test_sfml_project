# TODO: 
Простое:
* Добавить сборку на гитлабе(simple pipeline is ready), нужно ещё добавить doxygen, проверку санитайезрами. В отдельных джобах.
* Тесты
* CMake доправить
* Заменить дубли в мапах на boost::multiindex.
* Убрать статистику в отдельный класс.
* Убрать shared_mutex из task.cpp и task.hpp

Чуть посложнее:
* Везде заменить сырые указатели на умные. Возможно, взять из boost.
* Меню, пауза и тд. В виде состояний (сделано).
* Пресеты, анимации, частицы, коллизии
* Разнести по потокам (только загрузка)
* Бизнес логика(серверая и клиентская часть, обработка комманд от пользователя, настройки разрешения, бинды кнопок)
* GUI(примитивный гуй добавил)
