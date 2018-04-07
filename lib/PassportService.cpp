# include "PassportService.h"

std::istream& operator>>(std::istream &in, Date &dt)
{
    std::string dt_str;
    in >> dt_str;
    dt.year_ = std::stoi(dt_str.substr(0, 4));
    dt.month_ = std::stoi(dt_str.substr(5, 2));
    dt.day_ = std::stoi(dt_str.substr(8, 2));
    return in;
}

std::ostream& operator<<(std::ostream &out, Date &dt)
{
    out << dt.year_ << '-' << dt.month_ << '-' << dt.day_;
    return out;
}

bool Date::operator==(const Date &other) const
{
    return year_ == other.year_ && month_ == other.month_ && day_ == other.day_;
}

const std::string PassportService::base_file_ = "passport_data.txt";

Passport::Passport(const Name &name, const Patronymic &patr,
                   const Surname &surn, const PassportNumber &num, Date b):
    name_(name), patr_(patr), surn_(surn), num_(num), birth_(b) {}

Passport::Passport(Name&& name, Patronymic&& patr, Surname&& surn, PassportNumber&& num, Date b):
    name_(std::move(name)), patr_(std::move(patr)), surn_(std::move(surn)), num_(std::move(num)), birth_(b) {}

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
        return nullptr;
    std::ifstream fin(base_file_);
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
            fin.close();
            PassportBuilder pb;
            pb.setName(name);
            pb.setPatronymic(patr);
            pb.setSurname(surn);
            pb.setPassportNumber(num);
            pb.setBirthDate(date_b);
            return pb.getResult();
        }
    }
    fin.close();
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
    std::ifstream fin(base_file_);
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