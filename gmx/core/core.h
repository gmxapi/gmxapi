/*
 * This file is part of the GROMACS molecular simulation package.
 *
 * Copyright (c) 2017, by the GROMACS development team, led by
 * Mark Abraham, David van der Spoel, Berk Hess, and Erik Lindahl,
 * and including many others, as listed in the AUTHORS file in the
 * top-level source directory and at http://www.gromacs.org.
 *
 * GROMACS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * GROMACS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GROMACS; if not, see
 * http://www.gnu.org/licenses, or write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.
 *
 * If you want to redistribute modifications to GROMACS, please
 * consider that scientific software is very special. Version
 * control is crucial - bugs must be traceable. We will be happy to
 * consider code for inclusion in the official distribution, but
 * derived work must not be called official GROMACS. Details are found
 * in the README & COPYING files - if they are missing, get the
 * official version at http://www.gromacs.org.
 *
 * To help us fund GROMACS development, we humbly ask that you cite
 * the research papers on the package. Check out http://www.gromacs.org.
 */

/*! \defgroup module_python Python module for accessing Gromacs library
 *  \internal
 * The Python module ``gmx`` consists of a high-level interface implemented in
 * pure Python and a low-level interface implemented as a C++ extension in the
 * submodule, gmx.core.
 */
/*! \internal \file
 * \brief Declares symbols to be exported to gmx.core Python module.
 *
 * Declares namespace gmx::pyapi
 * \ingroup module_python
 */
#ifndef GMXPY_CORE_H
#define GMXPY_CORE_H

#include "gmxapi/gmxapi.h"

#include <string>

namespace pybind11
{
class module;
}


/*! \brief API client code from which to export Python bindings
 *
 * gmxpy is not a public interface. It implements bindings for the public
 * Python API in the C++ Python extension it produces, and it uses the public
 * C++ Gromacs API, but is itself an API *client* and its C++ interfaces are not
 * intended to be used in external code.
 * \internal
 * \ingroup module_python
 */
namespace gmxpy
{

/*! \brief Base class for Gromacs modules exported to Python
 *
 * PyGmxModule objects provide sufficient interface to bind with Runners.
 * Derived classes may provide additional interfaces.
 *
 * \internal
 * \ingroup module_python
 */
class PyGmxModule
{
    public:
        PyGmxModule()                               = default;
        PyGmxModule(const PyGmxModule &)            = default;
        PyGmxModule(PyGmxModule&&) noexcept         = default;
        virtual ~PyGmxModule()                      = default;
        PyGmxModule &operator=(const PyGmxModule &) = default;
        PyGmxModule& operator=(PyGmxModule&&) noexcept      = default;

        /*!
         * \brief Generic string output.
         *
         * Provide a generic way to implement simple self-representation. Optionally implemented
         * to allows for some trivial
         * introspection and/or runtime debugging. May ultimately be used as the hook for __str__()
         * or __repr__().
         * \return some useful information on the type or state of the object in string form.
         */
        virtual std::string info() { return ""; };
};

/*! \brief Generic return value for API calls.
 *
 * \internal
 * \ingroup module_python
 */
class PyStatus
{
    public:
        PyStatus() : success_(false) {};
        PyStatus(const PyStatus &status) : success_{status.success_} {};
        virtual ~PyStatus()         = default;

        explicit PyStatus(const bool &status) : success_(status) {};
        explicit PyStatus(const gmxapi::Status status) : success_(status.success()) {};

        bool success() const { return success_; };

    private:
        bool success_{false};
};

}      // end namespace gmxpy

#endif // PYGMX_CORE_H