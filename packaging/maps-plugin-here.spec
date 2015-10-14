Name:       maps-plugin-here
Summary:    Tizen HERE Maps Plug-in Library
Version:    0.1.6
Release:    1
Group:      Location/Libraries
License:    Apache-2.0 and HERE
Source0:    %{name}-%{version}.tar.gz
ExclusiveArch:  %ix86 x86_64 %arm aarch64

BuildRequires: cmake
# for here plugin
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(gmodule-2.0)
BuildRequires: pkgconfig(libxml-2.0)
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(capi-maps-service)
BuildRequires: capi-maps-service-plugin-devel
BuildRequires: pkgconfig(capi-network-connection)
BuildRequires: pkgconfig(capi-appfw-app-manager)
# for here engine
BuildRequires: pkgconfig(libcurl)
BuildRequires: pkgconfig(json-c)
BuildRequires: pkgconfig(libpng)
BuildRequires: pkgconfig(capi-system-info)
BuildRequires: pkgconfig(cairo)
BuildRequires: pkgconfig(evas)
BuildRequires: boost-devel

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
This packages provides Plugin APIs capsulating HERE Maps Engine Library for Maps Service Library.

%prep
%setup -q

%build
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DARCH=%{ARCH}
#make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}

mkdir -p %{buildroot}%{_prefix}/lib/maps/plugins/
cp -a %{ARCH}/libmaps-plugin-here.so* %{buildroot}%{_prefix}/lib/maps/plugins/
cp -a %{ARCH}/libheremaps-engine.so* %{buildroot}%{_prefix}/lib/

%files
%manifest maps-plugin-here.manifest
%defattr(-,root,root,-)
%{_prefix}/lib/maps/plugins/libmaps-plugin-here.so*
%{_prefix}/lib/libheremaps-engine.so*
/usr/share/license/maps-plugin-here
