Name:       maps-plugin-here
Summary:    Tizen HERE Maps Plug-in Library
Version:    0.2.0
Release:    1
Group:      Location/Libraries
License:    Apache-2.0 and HERE
Source0:    %{name}-%{version}.tar.gz
ExclusiveArch:  %ix86 x86_64 %arm aarch64

BuildRequires: cmake
# for here plugin
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(gio-2.0)
BuildRequires: pkgconfig(gio-unix-2.0)
BuildRequires: pkgconfig(gmodule-2.0)
BuildRequires: pkgconfig(libxml-2.0)
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(capi-maps-service)
BuildRequires: capi-maps-service-plugin-devel
BuildRequires: pkgconfig(capi-network-connection)
BuildRequires: pkgconfig(capi-appfw-app-manager)
BuildRequires: pkgconfig(capi-appfw-application)
BuildRequires: pkgconfig(capi-system-info)
BuildRequires: pkgconfig(efl-extension)
BuildRequires: pkgconfig(elementary)
BuildRequires: pkgconfig(vconf)
BuildRequires: pkgconfig(appcore-efl)
BuildRequires: pkgconfig(ecore)
BuildRequires: pkgconfig(evas)
BuildRequires: gettext-tools
# for here engine
BuildRequires: pkgconfig(libcurl)
BuildRequires: pkgconfig(json-c)
BuildRequires: pkgconfig(libpng)
BuildRequires: pkgconfig(cairo)
BuildRequires: boost-devel
#
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%ifarch %arm
%define ARCH arm
%endif

%ifarch aarch64
%define ARCH aarch64
%endif

%ifarch %ix86
%define ARCH i586
%endif

%ifarch x86_64
%define ARCH x86_64
%endif

%description
This package provides Plugin APIs capsulating HERE Maps Engine Library for Maps Service Library.

%prep
%setup -q

%build
%if 0%{?tizen_build_binary_release_type_eng}
export CFLAGS="$CFLAGS -DTIZEN_ENGINEER_MODE -g"
export CXXFLAGS="$CXXFLAGS -DTIZEN_ENGINEER_MODE -g"
export FFLAGS="$FFLAGS -DTIZEN_ENGINEER_MODE"
%endif

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DMAJORVER=${MAJORVER} -DFULLVER=%{version} -DLIBDIR=lib -DARCH=%{ARCH} -DSYSCONF_DIR=%{_sysconfdir}
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
cp -a lib/%{ARCH}/libheremaps-engine.so* %{buildroot}%{_prefix}/lib/

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%manifest maps-plugin-here.manifest
%defattr(-,root,root,-)
%{_prefix}/lib/maps/plugins/libmaps-plugin-here.so*
%{_prefix}/lib/libheremaps-engine.so*
/usr/share/license/maps-plugin-here


%package -n org.tizen.heremaps-uc
Summary:    HereMaps UC popup
Requires:   %{name} = %{version}-%{release}

%description -n org.tizen.heremaps-uc
This package provides UI interface to get consents from users to the HERE platform Service.

%files -n org.tizen.heremaps-uc
%manifest heremaps-uc/org.tizen.heremaps-uc.manifest
%defattr(-,root,root,-)
/usr/apps/org.tizen.heremaps-uc/bin/*
/usr/apps/org.tizen.heremaps-uc/res/locale
/usr/share/packages/org.tizen.heremaps-uc.xml


%package -n heremaps-uc-launcher
Summary:    HereMpas-UC Launcher deamon
Requires:   %{name} = %{version}-%{release}

%description -n heremaps-uc-launcher
This package is for launching the org.tizen.heremaps-uc application. 

%files -n heremaps-uc-launcher
%manifest heremaps-uc-launcher/heremaps-uc-launcher.manifest
%defattr(-,root,root,-)
/usr/bin/heremaps-uc-launcher
/usr/share/dbus-1/services/org.tizen.lbs.Providers.HereMapsUCLauncher.service
%config %{_sysconfdir}/dbus-1/session.d/heremaps-uc-launcher.conf
