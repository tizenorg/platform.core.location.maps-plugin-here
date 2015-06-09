Name:       maps-plugin-here
Summary:    Tizen HERE Maps Plug-in Library
Version:    0.1.2
Release:    1
Group:      Location/Libraries
License:    Apache-2.0 and HERE
Source0:    %{name}-%{version}.tar.gz

BuildRequires: cmake

%ifarch {arm}
%define ARCH arm
%else
%define ARCH i586 
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

%files
%{_libdir}/maps/plugins/libmaps-plugin-here.so
%{_libdir}/libheremaps-engine.so
