/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 *  Copyright (C) 2011
 *  Michael Natterer <michael.natterer@lanedo.com>
 *  Kristian Rietveld <kris@lanedo.com>
 *  Christian Dywan <christian@lanedo.com>
 *  Lionel Dricot <lionel.dricot@lanedo.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General
 *  Public License along with this library; if not, write to the
 *  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301 USA 
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *************************************************************************/

#ifndef _Addon_HXX
#define _Addon_HXX

#include "settings.hxx"
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <cppuhelper/implbase4.hxx>

namespace css = com::sun::star;

namespace com
{
    namespace sun
    {
        namespace star
        {
            namespace frame
            {
                class XFrame;
            }
        }
    }
}

#define IMPLEMENTATION_NAME "com.lanedo.webdavui"

class Addon : public cppu::WeakImplHelper4
<
    css::frame::XDispatchProvider,
    css::frame::XDispatch,
    css::lang::XInitialization,
    css::lang::XServiceInfo
>
{
private:
    css::uno::Reference< css::uno::XComponentContext > mxContext;
    css::uno::Reference< css::frame::XFrame > mxFrame;
    WebDAVUI::Settings* mSettings;

public:
    Addon( const css::uno::Reference< css::uno::XComponentContext > &rxContext)
        : mxContext( rxContext ) {}

    // XDispatchProvider
    virtual css::uno::Reference< css::frame::XDispatch >
        SAL_CALL queryDispatch( const css::util::URL& aURL,
                                const rtl::OUString&  sTargetFrameName,
                                sal_Int32             nSearchFlags )
        throw( css::uno::RuntimeException );
    virtual css::uno::Sequence < css::uno::Reference< css::frame::XDispatch > >
        SAL_CALL queryDispatches( const css::uno::Sequence < css::frame::DispatchDescriptor >& seqDescriptor )
        throw( css::uno::RuntimeException );

    // XDispatch
    virtual void SAL_CALL dispatch( const css::util::URL&                                  aURL,
                                    const css::uno::Sequence< css::beans::PropertyValue >& lArgs )
        throw (css::uno::RuntimeException);
    virtual void SAL_CALL addStatusListener( const css::uno::Reference< css::frame::XStatusListener >& xControl,
                                             const css::util::URL&                                     aURL )
        throw (css::uno::RuntimeException);
    virtual void SAL_CALL removeStatusListener( const css::uno::Reference< css::frame::XStatusListener >& xControl,
                                                const css::util::URL&                                     aURL )
        throw (css::uno::RuntimeException);

    // XInitialization
    virtual void SAL_CALL initialize( const css::uno::Sequence< css::uno::Any >& aArguments )
        throw (css::uno::Exception, css::uno::RuntimeException);

    // XServiceInfo
    virtual rtl::OUString SAL_CALL getImplementationName(  )
        throw (css::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const rtl::OUString& ServiceName )
        throw (css::uno::RuntimeException);
    virtual css::uno::Sequence< rtl::OUString > SAL_CALL getSupportedServiceNames(  )
        throw (css::uno::RuntimeException);
};

rtl::OUString Addon_getImplementationName()
    throw ( css::uno::RuntimeException );

sal_Bool SAL_CALL Addon_supportsService( const rtl::OUString& ServiceName )
    throw ( css::uno::RuntimeException );

css::uno::Sequence< rtl::OUString > SAL_CALL Addon_getSupportedServiceNames(  )
    throw ( css::uno::RuntimeException );

css::uno::Reference< css::uno::XInterface >
SAL_CALL Addon_createInstance( const css::uno::Reference< css::uno::XComponentContext > & rSMgr)
    throw ( css::uno::Exception );

#endif // _Addon_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
