# include <memory>
# include <fstream>
# include <string>
# include "Card.h"

/**
 * @brief Simple structure for dealing with date
 * @details May be read from istream and may be written to ostream
 */
class Date
{
public:
    friend std::istream& operator>>(std::istream&, Date&);
    friend std::ostream& operator<<(std::ostream&, Date&);

    bool operator==(const Date&) const;
private:
    size_t year_, month_, day_;
};

/**
 * @brief operator>> for input from istream Date object
 * @details Format: YYYY-MM-DD
 */
std::istream& operator>>(std::istream&, Date&);

/**
 * @brief operator<< for output to ostream Date object
 * @details Format YYYY-MM-DD
 */
std::ostream& operator<<(std::ostream&, Date&);

using Name = std::string;
using Surname = std::string;
using Patronymic = std::string;
using PassportNumber = std::string;

/**
 * @brief A class for simulating capability of passport
 * @details Stores name, surname, patronymic, card number, date of birth as private fields.
 *          User can get it them through getters.
 */
class Passport
{
public:
    Passport() = default;
    Passport(const Name&, const Patronymic&, const Surname&, const PassportNumber&, Date);
    Passport(Name&&, Patronymic&&, Surname&&, PassportNumber&&, Date);
    Passport(const Passport&) = default;
    Passport(Passport&&) = default;
    ~Passport() = default;

    Name getName() const;
    Patronymic getPatronymic() const;
    Surname getSurname() const;
    PassportNumber getNumber() const;

    /**
     * @brief A function for getting the surname, name and patronymic as one string
     */
    std::string getFullName() const;
    Date getDateBirth() const;
private:
    Name name_;
    Surname surn_;
    Patronymic patr_;
    PassportNumber num_;
    Date birth_;
};

/**
 * @brief Base service for getting documents data
 * @details Stub for sending request on server and getting the data: first name, patronymic, last name,
 * passport number, birth date
 */
class PassportService
{
public:
    PassportService() = default;
    PassportService(const PassportService &other) = default;

    /**
     * @brief Gets passport data by card from server
     * @param card Data of currently considered card
     * @return shared_ptr to Passport from the base. If no found returns nullptr.
     */
    std::shared_ptr<Passport> getPassport(const std::shared_ptr<Card> &card) const;

    /**
     * @brief Check if the passport is valid.
     * @param pass shared_ptr to Passport.
     * @return If passport haven't found in the base returns false (including the case of pass == nullptr).
     * Otherwise returns true.
     */
    bool passportValidation(const std::shared_ptr<Passport> &pass) const;
private:
    static const std::string base_file_;

    /**
     * @brief Checks if the data of the passport is the same as given as arguments.
     * @return true if the data belongs to the passport, and false, otherwise.
     */
    static bool checkEquivalent(const std::shared_ptr<Passport>&, const Name&, const Patronymic&, 
                                const Surname&, const PassportNumber&, Date);
};