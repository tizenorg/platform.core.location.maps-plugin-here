Name:       maps-plugin-here
Summary:    Tizen Maps Library
Version:    0.0.3
Release:    1
Group:      Location/Libraries
License:    Apache-2.0 and HERE Proprietary
Source0:    %{name}-%{version}.tar.gz

BuildRequires:  cmake

%ifarch {arm}
%define ARCH arm
%else
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
