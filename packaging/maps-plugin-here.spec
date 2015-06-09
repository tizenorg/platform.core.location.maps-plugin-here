Name:       maps-plugin-here
Summary:    Tizen HERE Maps Plug-in Library
Version:    0.1.2
Release:    1
Group:      Location/Libraries
License:    Apache-2.0 and HERE
Source0:    %{name}-%{version}.tar.gz
ExclusiveArch:  %ix86 x86_64 %arm aarch64

BuildRequires: cmake

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

mkdir -p %{buildroot}%{_prefix}/lib/maps/plugins/
cp -a %{ARCH}/libmaps-plugin-here.so* %{buildroot}%{_prefix}/lib/maps/plugins/
cp -a %{ARCH}/libheremaps-engine.so* %{buildroot}%{_prefix}/lib/

%files
%{_prefix}/lib/maps/plugins/libmaps-plugin-here.so*
%{_prefix}/lib/libheremaps-engine.so*
