# include <iostream>
# include "lib/Terminal.h"
# include "lib/PassportService.h"
# include "lib/PassportManager.h"

template<Id ID>
class SimpleTerminal : public ITerminal
{
public:
    SimpleTerminal() = default;
    ~SimpleTerminal() = default;
    virtual std::shared_ptr<Card> getCard() override
    {
        return std::shared_ptr<Card>(new Card(ID));
    }
};

static PassportManager pm;

TEST(PassportTest, ValidPassport)
{
    SimpleTerminal<0> term;
    std::shared_ptr<Card> card = term.getCard();
    EXPECT_EQ(card->getId(), 0);
    std::shared_ptr<Passport> passp = pm.getPassport(card);
    EXPECT_EQ(passp->getFullName(), "Utushkin Maxim Alexandrovich");
    EXPECT_EQ(passp->getDateBirth(), Date(1999, 06, 07));
    EXPECT_EQ(passp->getNumber(), "1234123456");
}

TEST(PassportTest, InvalidPassport)
{
    SimpleTerminal<100> term;
    std::shared_ptr<Card> card = term.getCard();
    std::shared_ptr<Passport> passp = pm.getPassport(card);
    EXPECT_EQ(passp, nullptr);
}