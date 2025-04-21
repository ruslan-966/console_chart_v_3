#pragma once

template <typename T>
class DataManager // Абстрактный класс, чтобы было удобно выбрать какой способ сохранения мы используем 
{
public:
	virtual void add(T&&) = 0;
	virtual void deleteAt(int i) = 0;
	virtual T get(int i) const = 0;
	virtual int getCount() const = 0;
	virtual bool find(T&& item, int& index) = 0;
};