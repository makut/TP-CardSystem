# pragma once
# include <map>
# include <set>
# include "PassportService.h"

/**
 * @brief Proxy of the PassportService class
 * @details Supports cache of recently got passports
 */
class PassportManager
{
public:
    PassportManager() = default;
    PassportManager(const PassportManager&) = default;
    ~PassportManager() = default;

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
    PassportService ps_;
    mutable std::map<Card, std::shared_ptr<Passport>> cache_;
    mutable std::set<std::shared_ptr<Passport>> passports_;
};