# include "PassportService.h"

Date::Date(size_t year, size_t month, size_t day) : year_(year), month_(month), day_(day) {}

std::istream& operator>>(std::istream &in, Date &dt)
{
    std::string dt_str;
    in >> dt_str;
    dt.year_ = std::stoi(dt_str.substr(0, 4));
    dt.month_ = std::stoi(dt_str.substr(5, 2));
    dt.day_ = std::stoi(dt_str.substr(8, 2));
    return in;
}

std::ostream& operator<<(std::ostream &out, const Date &dt)
{
    out << dt.year_ << '-' << dt.month_ << '-' << dt.day_;
    return out;
}

bool Date::operator==(const Date &other) const
{
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}

bool Date::operator<(const Date &other) const
{
    if (year_ < other.year_)
        return true;
    else if (year_ > other.year_)
        return false;
    if (month_ < other.month_)
        return true;
    else if (month_ > other.month_)
        return false;
    if (day_ < other.day_)
        return true;
    return false;
}

const std::string PassportService::data_ = "0 Maxim Alexandrovich Utushkin 1234123456 1999-06-07\n\
1 Ivan Ivanovich Ivanov 2345283906 1960-03-04\n\
2 Petr Andreevich Kulagin 4932869324 1998-10-18\n\
3 Roman Viktorovich Gorb 3405963023 1999-09-03\n\
4 Sergey Armenovich Grigoriants 2304959614 2000-02-27\n\
5 Amir Marselevich Yagudin 8934629585 2000-04-21\n";

Passport::Passport(const Name &name, const Patronymic &patr,
                   const Surname &surn, const PassportNumber &num, Date b):
    name_(name), patr_(patr), surn_(surn), num_(num), birth_(b) {}

Passport::Passport(Name&& name, Patronymic&& patr, Surname&& surn, PassportNumber&& num, Date b):
    name_(std::move(name)), patr_(std::move(patr)), surn_(std::move(surn)), num_(std::move(num)), birth_(b) {}

bool Passport::operator<(const Passport &other) const
{
    if (name_ < other.name_)
        return true;
    else if (name_ > other.name_)
        return false;
    if (surn_ < other.surn_)
        return true;
    else if (surn_ > other.surn_)
        return false;
    if (patr_ < other.patr_)
        return true;
    else if (patr_ > other.patr_)
        return false;
    if (num_ < other.num_)
        return true;
    else if (num_ > other.num_)
        return false;
    if (birth_ < other.birth_)
        return true;
    return false;
}

Name Passport::getName() const
{
    return name_;
}

Patronymic Passport::getPatronymic() const
{
    return patr_;
}

Surname Passport::getSurname() const
{
    return surn_;
}

std::string Passport::getFullName() const
{
    return surn_ + " " + name_ + " " + patr_;
}

PassportNumber Passport::getNumber() const
{
    return num_;
}

Date Passport::getDateBirth() const
{
    return birth_;
}

void PassportBuilder::setName(const Name &name)
{
    name_ = name;
}

void PassportBuilder::setName(Name&& other)
{
    name_ = std::move(other);
}

void PassportBuilder::setPatronymic(const Patronymic &patr)
{
    patr_ = patr;
}

void PassportBuilder::setPatronymic(Patronymic&& patr)
{
    patr_ = std::move(patr);
}

void PassportBuilder::setSurname(const Surname &surn)
{
    surn_ = surn;
}

void PassportBuilder::setSurname(Surname&& surn)
{
    surn_ = std::move(surn);
}

void PassportBuilder::setPassportNumber(const PassportNumber &num)
{
    num_ = num;
}

void PassportBuilder::setPassportNumber(PassportNumber&& num)
{
    num_ = std::move(num);
}

void PassportBuilder::setBirthDate(const Date &dt)
{
    birth_ = dt;
}

std::shared_ptr<Passport> PassportBuilder::getResult() const
{
    return std::shared_ptr<Passport>(new Passport(name_, patr_, surn_, num_, birth_));
}

std::shared_ptr<Passport> PassportService::getPassport(const std::shared_ptr<Card> &card) const
{
    if (card == nullptr)
    {
        return nullptr;
    }
    std::stringstream fin(data_);
    Id curr;
    while (fin >> curr)
    {
        Name name;
        Patronymic patr;
        Surname surn;
        PassportNumber num;
        Date date_b;
        fin >> name >> patr >> surn >> num >> date_b;
        if (curr == card->getId())
        {
            PassportBuilder pb;
            pb.setName(name);
            pb.setPatronymic(patr);
            pb.setSurname(surn);
            pb.setPassportNumber(num);
            pb.setBirthDate(date_b);
            return pb.getResult();
        }
    }
    return nullptr;
}

bool PassportService::checkEquivalent(const std::shared_ptr<Passport> &pass, const Name &nm,
                                      const Patronymic &patr, const Surname &surn, const PassportNumber &num,
                                      Date birth_date)
{
    return (pass->getName() == nm && pass->getPatronymic() == patr && pass->getSurname() == surn &&
            pass->getNumber() == num && pass->getDateBirth() == birth_date);
}

bool PassportService::passportValidation(const std::shared_ptr<Passport> &pass) const
{
    if (pass == nullptr)
        return false;
    std::stringstream fin(data_);
    Id curr;
    while (fin >> curr)
    {
        Name name;
        Patronymic patr;
        Surname surn;
        PassportNumber num;
        Date date_b;
        fin >> name >> patr >> surn >> num >> date_b;
        if (checkEquivalent(pass, name, patr, surn, num, date_b))
            return true;
    }
    return false;
}