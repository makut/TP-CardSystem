# include "Card.h"

Card::Card(const Id &id) : id_(id) {}
Card::Card(const std::shared_ptr<Card> &other) : id_(other->id_) {}

Id Card::getId() const
{
    return id_;
}

bool Card::operator<(const Card &other) const
{
    return getId() < other.getId();
}