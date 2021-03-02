/*
 *    Copyright (c) 2009-2021 Nuovation System Designs, LLC
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file defines a container-style template to effect an
 *      action or method chain for concrete instances of an abstract
 *      base class in which a sequence of one or more identical
 *      operations need to be carried out for each concrete instance
 *      in the chain against a single input.
 *
 *      Examples of chain template usage include allow/deny processing
 *      or multiple, sequential formats and writes to various output
 *      destinations for a single input.
 */

#ifndef LOGUTILITIES_LOGCHAIN_HPP
#define LOGUTILITIES_LOGCHAIN_HPP

#include <list>
#include <memory>

#include <boost/next_prior.hpp>
#include <boost/shared_ptr.hpp>

namespace Nuovations
{

    namespace Log
    {

        /**
         *  A template to effect a chain-like container-style object
         *  for an action or method chain for concrete instances of
         *  an abstract base class in which a sequence of one or
         *  more identical operations need to be carried out for
         *  each concrete instance in the chain against a single
         *  input.
         *
         *  Examples of chain template usage include allow/deny
         *  processing or multiple, sequential formats and writes to
         *  various output destinations for a single input.
         *
         *  @tparam  Base  The abstract base type of all objects in
         *                 the chain.
         *
         */
        template <typename Base>
        class Chain
        {
        protected:
            /**
             *  Underlying container type for the chain.
             */
            typedef std::list<Base *>                  container_type;

        private:
            typedef typename container_type::size_type size_type;

        protected:
            /**
             *  @brief
             *    This is a class default constructor.
             *
             */
            Chain(void) :
                mImplementation(new Implementation)
            {
                return;
            }

            /**
             *  @brief
             *    This is a class copy constructor.
             *
             *  @param[in]  inChain  An immutable reference to the chain
             *                       to be copied.
             *
             */
            Chain(const Chain & inChain) :
                mImplementation(inChain.mImplementation)
            {
                return;
            }

        public:
            virtual ~Chain(void)
            {
                return;
            }

            /**
             *  @brief
             *    Attempt to return a derived type pointer to the
             *    specified object link in the chain.
             *
             *  @tparam     Derived  The derived type for the object in
             *                       the chain to be returned.
             *
             *  @param[in]  inIndex  The zero-based index of the object
             *                       link in the chain to return.
             *
             *  @returns
             *    A pointer to the requested object link if found;
             *    otherwise, NULL.
             *
             */
            template <typename Derived>
            Derived * Link(const size_type &inIndex) const
            {
                if (inIndex >= Size()) {
                    return (NULL);
                }

                return (static_cast<Derived *>(*boost::next(Container().begin(), inIndex)));
            }

            /**
             *  @brief
             *    Attempt to push a copy (that is, add) of the
             *    specified derived chain link object onto the
             *    trailing link of the chain.
             *
             *  @tparam     Derived  The derived type for the object
             *                       in the chain to be pushed/added.
             *  @param[in]  inLink   An immutable reference to the
             *                       derived chain link object to be
             *                       added to the chain.
             *
             */
            template <typename Derived>
            void Push(const Derived & inLink)
            {
#if __cplusplus >= 201103L
                std::unique_ptr<Derived> theLink(new Derived(inLink));
#else
                std::auto_ptr<Derived> theLink(new Derived(inLink));
#endif

                Container().push_back(theLink.get());

                theLink.release();
            }

            /**
             *  @brief
             *    Attempt to return a reference to the derive chain
             *    link object at the leading link of the chain.
             *
             *  @tparam     Derived  The derived type for the object
             *                       in the chain to be returned.
             *
             *  @returns
             *    A reference to the leading link of the chain.
             */
            template <typename Derived>
            Derived & Front(void)
            {
                return (*Container().front());
            }

            /**
             *  @brief
             *   Remove the trailing link of the chain.
             *
             */
            void Pop(void)
            {
                Base *theLink = NULL;

                std::swap(theLink, Container().back());

                delete theLink;

                Container().pop_back();
            }

            /**
             *  @brief
             *    Test whether the chain has any links.
             *
             *  @returns
             *     True if the chain has no links; otherwise, false.
             *
             */
            bool Empty(void) const
            {
                return (Container().empty());
            }

            /**
             *  @brief
             *    Return the number of links in the chain.
             *
             *  @returns
             *    The number of links in the chain.
             *
             */
            size_type Size(void) const
            {
                return (Container().size());
            }

            /**
             *  @brief
             *    Removes all links from the chain (which are
             *    destroyed), leaving the chain with a size of zero
             *    (0).
             *
             */
            void Reset(void)
            {
                mImplementation->Reset();
            }

        protected:
            /**
             *  @brief
             *    Returns a reference to the underlying chain
             *    container.
             *
             *  @returns
             *    A reference to the underlying chain container.
             *
             */
            container_type & Container(void)
            {
                return (mImplementation->mLinks);
            }

            /**
             *  @brief
             *    Returns an immutable reference to the underlying
             *    chain container.
             *
             *  @returns
             *    An immutable reference to the underlying chain
             *    container.
             *
             */
            const container_type & Container(void) const
            {
                return (mImplementation->mLinks);
            }


        private:
            struct Implementation
            {
                Implementation(void)
                {
                    return;
                }

                ~Implementation(void)
                {
                    Reset();
                }

                void Reset(void)
                {
                    typedef typename container_type::iterator iterator;
                    iterator current = mLinks.begin();
                    iterator last = mLinks.end();

                    while (current != last) {
                        Base *theLink = NULL;

                        std::swap(theLink, *current);

                        delete theLink;

                        std::advance(current, 1);
                    }

                    mLinks.clear();
                }

                container_type  mLinks;
            };

            boost::shared_ptr<Implementation> mImplementation;
        };

    }; // namespace Log

}; // namespace Nuovations

#endif /* LOGUTILITIES_LOGCHAIN_HPP */
