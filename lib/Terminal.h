# include <memory>
# include "Card.h"

/**
 * @brief Interface for terminal
 * @details It is needed to combine all the possible user terminals. 
 * It may return a Card object by a real card inserted into the card reader.
 * @return [description]
 */
class ITerminal
{
public:
    /**
     * @brief Returns the object linked with the card inserted into the terminal card reader
     * @return shared_ptr to Card. If no valid card insert returns nullptr.
     */
    virtual std::shared_ptr<Card> getCard() = 0;
    virtual ~ITerminal() = 0;
};