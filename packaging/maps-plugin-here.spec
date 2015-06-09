Name:       maps-plugin-here-a
Summary:    Tizen Maps Library
Version:    0.0.4
Release:    1
Group:      Framework/maps
License:    SAMSUNG Proprietary, HERE Proprietary
Source0:    %{name}-%{version}.tar.gz

%ifarch armv7l
%define ARCH armv7l
%endif

%ifarch i586
%define ARCH i586
%endif

%description
Tizen Shared Library for HERE Maps

%prep
%setup -q

%build
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DARCH=%{ARCH}
#make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%files
%{_libdir}/maps/plugins/libmaps-plugin-here.so
%{_libdir}/libheremaps-engine.so
