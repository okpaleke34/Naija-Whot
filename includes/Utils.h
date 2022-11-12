#pragma once
class Utils {
public:
    //1. C++ Templeting 
    //because 1. To make the function resuable for other vector types 2.the Utils Header have to be imported before Card header so Card object cannot be passed as a parameter 
    template < typename T>
    //(Card* newCard)
    std::pair<bool, int > findInVector(const std::vector<T*>& vecOfElements, const T *element)
    {
        std::pair<bool, int > result;
        // Find given element in vector
        auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
        if (it != vecOfElements.end())
        {
            result.second = distance(vecOfElements.begin(), it);
            result.first = true;
        }
        else
        {
            result.first = false;
            result.second = -1;
        }
        return result;
    }
};