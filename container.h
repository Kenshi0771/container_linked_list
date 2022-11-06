#include "stdbool.h"
#include "stdint.h"
#include "cstdlib"
#include <cassert>
#include <iostream>

namespace Utils
{

    template <class T>
    class container
    {
        struct Unit
        {
            size_t index;
            Unit *prev;
            Unit *next;
            T data;
        };

    protected:
        Unit *_first;
        Unit *_last;
        Unit *_lastRead;
        int _count;

    public:
        container() : _first(nullptr), _last(nullptr), _lastRead(nullptr), _count(0)
        {
        }

        ~container()
        {
            Unit *curr = _first;
            do
            {
                Unit *next = curr->next;
                delete curr;
                curr = next;
            } while (curr);
        }

        bool pushBack(const T &val)
        {
            Unit *tmp = new Unit();

            if (!tmp)
                return false;

            tmp->data = val;

            tmp->next = nullptr;

            if (!_count)
            {
                tmp->prev = nullptr;

                _first = tmp;
                _last = tmp;
            }
            else
            {
                _last->next = tmp;
            }
            _last = tmp;
            tmp->index = _count;
            _count++;
            return true;
        }

        T &getItem(size_t index)
        {
            assert(index < _count);
            assert(_first);
            Unit *curr = _first;
            do
            {
                if (curr->index == index)
                    return curr->data;
                curr = curr->next;
            } while (curr);

            return curr->data;
        }

        T &operator[](size_t index)
        {
            return getItem(index);
        }

        const T &operator[](size_t index) const
        {
            return getItem(index);
        }

        const size_t getCount()
        {
            return _count;
        }
    };

}