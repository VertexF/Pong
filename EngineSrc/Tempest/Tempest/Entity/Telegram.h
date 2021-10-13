#ifndef TELEGRAM_HDR
#define TELEGRAM_HDR

#include <iostream>
#include <cmath>

namespace
{
    //__________________________________________________________________________
    //These telegrams will be stored in a priority queue. Therefore the > operator
    //needs to be overloaded so the priority queue can sort the telegrams by 
    //priority. Note how the times must be smaller delay before two Telegrams are
    //considered unique.
    static const double smallestDelay = 0.25;
}

namespace Tempest 
{
    //! This defines a telegram. A telegram is a data structure that records 
    //! information required to dispatch messages. Messages are used by game agents
    //! to communicate with each other.
    struct Telegram 
    {
        Telegram() : sender(-1), receiver(-1), message(-1), dispatchTime(-1.0), 
            extraInfo(nullptr)
        {
        }

        Telegram(int sender, int receiver, int message, double time, void* info = nullptr) : 
            sender(sender), receiver(receiver), message(message), dispatchTime(time), 
            extraInfo(info)
        {
        }

        //The eneity that sent this telegram.
        int sender;
        //The eneity that is to receive this telegram.
        int receiver;
        //The message itself. These are all emumerated in the file "MessageTypes.h"
        int message;

        //Messages can be dispatched immediately or delayed for a specified amount
        //of time. If a delay is necessary this field is stamped with the time the 
        //message should be dispatched.
        double dispatchTime;

        //Any additional information that may accompany the message.
        void* extraInfo;
    };

    inline bool operator!=(const Telegram& tele1, const Telegram& tele2)
    {
        return (std::fabs(tele1.dispatchTime - tele2.dispatchTime) >= smallestDelay &&
            (tele1.sender != tele2.sender) &&
            (tele1.receiver != tele2.receiver) &&
            tele1.message != tele2.message);
    }

    inline bool operator<(const Telegram& tele1, const Telegram& tele2)
    {
        bool success = false;
        if (tele1 != tele2)
        {
            success = (tele1.dispatchTime < tele2.dispatchTime);
        }
        return success;
    }

    inline std::ostream& operator<<(std::ostream& os, const Telegram& tele)
    {
        os << "Time: " << tele.dispatchTime << " Sender: " << tele.sender <<
            " Receiver: " << tele.receiver << " Message: " << tele.message;

        return os;
    }

    //Handy helper function for deferenceing the extraInfo field of the telegram
    //to the required type.
    template<class T>
    inline T deferenceToType(void* voidPointer)
    {
        return *(T*)(voidPointer);
    }
}

#endif // !TELEGRAM_HDR
