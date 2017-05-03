# MeasurementKit 0.6.0-beta [2017-05-02]

- Backport build system changes from master
- Sync files in top-level directory with master
- Backport test/net/connect.cpp fix for libevent-2.1
- Add NOTICE file, forgotten in previous PR
- Manually resolve ChangeLog.md conflict
- Add `node_modules` to .gitignore
- Backport `MK_MOCK()` simplification from master
- Backport HHFM and meek tests from master
- Also update .gitignore

# MeasurementKit 0.4.4 [2017-05-02]

- Disable test for bacardi.com
- Backport #1186 to stable branch
- Update to latest stable dependencies
- Backport #1163 to stable branch
- Backport #1179 to stable branch

# MeasurementKit 0.5.0-alpha [2017-04-11]

- Force the library to use the system resolver (#972)
- Add OONI bouncer support (#967)
- Refine and finish bouncer implementation (#1014)
- Add documentation for OONI's bouncer (#1032)
- Move dns resolution function from net to dns (#1022)
- Simple refactoring of system resolver (#1040)
- Forward port patch #1066 to master (#1067)
- build/dependency: implement quick git clone (#1068)
- build/dependency: factor more operations (#1069)
- Start cleaning up docker build system (#1070)
- Finish cleaning up docker build system (#1071)
- README.md: attempt to fix coveralls badge (#1072)
- travis: conditional build depending on branch (#1074)
- More cleanups of the CI subsystem (#1075)
- Increase code coverage a bit (#1036)
- Attempt to fix issue with case sensitive drive (#1076) (#1077)
- Backport simple hotfixes from #1017 (#1091)
- Tweak build/ios/cross (#1094)
- http: extract interesting stuff from #929 (#1095)
- Repair regress tests (#1117)
- Tweak README.md and ChangeLog.md (#1119)
- Fix uninitialized values according to Valgrind (#1118)
- Remove bashism (#1145)
- configure.ac: add /usr/local by default on macOS (#1151)
- test/net/connect.cpp: libevent 2.1.8 compat (#1152)
- Make Transport more OO (#1153)
- net: move most close logic in emitter (#1154)
- ooni/templates http: include all request/responses (#1149)
- replace short PGP key fingerprint with long one (#1157)
- Refactor cmdline to have OONI-like interface (#1156)
- net: further tweak the transport model (#1155)
- Repair broken test/ooni/utils.cpp (#1164)
- Fix `unknown_failure 3` bug (#1162)
- Repair regress tests after travis failure (#1166)
- build/ci/travis: fix branch name detection logic (#1167)
- http: refactor redirect logic (#1168)
- ooni/template.cpp: don't assume `!!response->request` (#1170)
- Finish fixing travis branch handling (#1171)
- common: add {start,end}swith (#1172)
- http::Response: init numbers to know value (#1174)
- http: treat EOF instead of response as error (#1175)
- Fix embarassing mk::endswith() bug (#1173)
- Fix `unknown_error_3009` bug (#1176)
- Fix report/entry.hpp w/ new NDK, nlohmann::json (#1177)
- Only run coveralls if we know the token (#1181)
- meek fronting nettest (#1141)
- Update to nlohmann/json v2.1.1 (#1179)
- mock.hpp: reduce implicit `MK_MOCK_NAMESPACE` magic (#1142)
- Start updating dependencies: the easy part (#1163)
- Update valgrind suppression files (#1186)
- Build and archive dependencies separately (#1185)
- Update README, license, badges (#1188)
- Refactor and improve build scripts (#1017)
- HTTP header fields manipulation test (#1146)

# MeasurementKit 0.4.3 [2017-03-14]

- Backport 5d88cf9ff (#1177) to stable branch

# MeasurementKit 0.4.2 [2017-03-12]

- Backport #1162: fix `unknown_failure 3` bug
- Backport #1163: repair regress tests after travis failure
- Backport #1164: repair broken test/ooni/utils.cpp
- Backport #1168: http: refactor redirect logic
- Backport #1170: ooni/template.cpp: don't assume `!!response->request`
- Backport #1172 and #1173: common: add {start,end}swith
- Backport #1174: http::Response: init numbers to known value
- Backport #1175: http: treat EOF-instead-of-response as error
- Backport #1176: Fix `unknown_error_3009` bug

# MeasurementKit 0.4.1 [2017-03-02]

- Backport #1149: ooni/templates http: include all request/responses

# MeasurementKit 0.4.0 [2017-02-13]

- Repair circle-ci build for stable (#1123)
- connect: support also ipv6 link local with scope (#1102)
- Fix gitlab on stable by using yakkety (#1133)
- Be more specific wrt connect() failure (#1126)
- Add a name to each error (#1134)

# MeasurementKit 0.4.0-beta.4 [2017-02-09]

- .gitlab-ci.yml: also build stable (#1122)
- http: fix EOF-implies-end-of-body logic (#1121)
- http: fix schema less redirect (#1124)

# MeasurementKit 0.4.0-beta.3 [2017-02-01]

- `ip_lookup()`: validate result as IP address (#1108)
- `web_connectivity`: do not `*request` unconditionally
- runnable: progress now accounts for `max_runtime`
- progress: also track opening/closing report
- The header key comparison MUST be done with the lowercase version
- Use std::transform to convert to lowercase
- Use transform also in another place

# MeasurementKit 0.4.0-beta.2 [2017-01-31]

- Start updating documentation for release 0.4.0 (#1082)
- report: Allow to specify application name and version (#1092)
- report: include the platform (#1093)
- Make sure http template produces good json (#1096)
- var.hpp: fix as() to use dynamic cast (#1090)
- test/net/connect.cpp: refactor to avoid global poller (#1099)
- connect: start fixing IPv6 addresses (#1100)
- net: start exposing network errors (#1101)
- Feature: NDT stats (#1089)
- Add regress tests for input processor (#1059)
- Use default backends when it makes sense (#1097)
- Propagate network errors (#1103)
- Fix: web connectivity segfault (#1107)
- `templates::http_request()`: scrub IP address (#1106)
- `web_connectivity`: pass headers to backend (#1111)

# MeasurementKit 0.4.0-beta.1 [2017-01-16]

- net: improve handling of address:port (#1079)
- `clang-format -i ooni/web_connectivity.cpp` (#1078)
- Attempt to fix issue with case sensitive drive (#1076)
- README.md: attempt to fix coveralls badge (#1073)
- travis: fix coveralls (#1066)

# MeasurementKit 0.4.0-beta [2017-01-13]

- Feature: recognize utf8 (#1062)
- Support for country-specific test lists (#1030)

# MeasurementKit 0.4.0-alpha.3 [2017-01-06]

- nettests: randomize input (#1029)
- Add workaround for Android with API < 21 (#1048)
- android build: simple changes backported from #1047 (#1049)
- More hotfix backports from #1047 (#1050)
- Fix API and ABI compatibility for old Androids (#1047)
- `system_resolver.hpp`: do not warn on getaddrinfo failure (#1055)

# MeasurementKit 0.4.0-alpha.2 [2016-12-28]

- runnable: implement `max_runtime` option (#1028)
- Fix libevent clock gettime (#1044)

# MeasurementKit 0.4.0-alpha.1 [2016-12-15]

- Improve `multi_ndt` entry format (#992)
- Fix: libressl ios build (#994)
- Refactor: ssl (#997)
- Write ssl context regress tests (#998)
- Implement mk::slurp() to read files at once (#996)
- BaseTest: add `on_logger_eof()` method (#1004)
- getaddrinfo: android dislikes `AI_V4MAPPED|AI_ALL` (#1005)
- logger: allow multiple `on_eof()` callbacks (#1006)
- runnable: allow multiple on-end callbacks (#1007)
- Use builtin CA file if CA file is missing and we're using libressl (#999)
- runnable: add `on_destroy()` callback (#1008)

# MeasurementKit 0.4.0-alpha [2016-12-07]

- cmdline.hpp: Use macros to simplify code (#858)
- Make `no_collector` / `no_file_report` options really usable (#860)
- Make sure filenames extension is .njson, not .json (#873)
- dns: pass logger to query() (#878)
- don't track njson files (#879)
- dns.hpp: pass a `Var<Message>` to the callback (#862)
- ssl: handle errors using callbacks not exceptions (#789)
- Start moving libevent code into a specific folder (#891)
- More abstract reactor API (#894)
- reactor: move more code from poller to here (#895)
- More reactor-related cleanups (#896)
- More maintenance of reactor and poller (#897)
- net: measure connect time during connect (#899)
- Prepare for required successful build only on travis (#902)
- ndt: multi stream test (#710)
- Implement and use `reactor->pollfd()` (#898)
- Add support for submitting reports via cloudfronted collectors (#907)
- http/request: don't redirect if `*max_request <= 0` (#910)
- Log dns debug to the correct logger (#912)
- travis: valgrind: update openssl.supp (#928)
- Move cmdline in src/measurement_kit (#930)
- collector_client.hpp: remove backward compat stuff (#931)
- version: use C linkage function (#932)
- Reactor should come before logger in function args (#933)
- ndt: exchange reactor and logger arguments (#934)
- reactor.hpp: add missing header (#936)
- Do not use `using namespace` in public headers (#937)
- Refactoring of the nettests layer (#938)
- nettests: move code from headers to .cpp files (#939)
- runner: hide implementation details (#940)
- net_test: less inline functions (#941)
- Merge net_test.hpp and ooni_test.hpp (#942)
- ooni_reporter: fix layers violation (#943)
- Divide net_test in base_test and runnable (#944)
- nettests: more refactoring (#945)
- Feature: ignore collector errors (#946)
- Move ooni_reporter in report module (#947)
- nettests: pass `Var<Entry>` to callback (#948)
- nettests: run() now uses the current thread (#949)
- dns: enums that should not conflict with windows (#951)
- Resolve hosts using the system resolver (#918)
- Support IPv6 link-local resolver (#915)
- logger: add callback for JSON encoded events (#956)
- ndt: print progress of the test (#958)
- Make sure we always store and submit report-id (#950)
- ndt: allow to specify alternative mlabns tool (#959)
- Move network utils code in net directory (#960)
- Always disable the Nagle algorithm (#961)
- Set CFLAGS et al. in configure (#963)
- Improve cmake for Unix (#965)
- Implement single+multiple stream NDT test (#968)
- Update dependencies for v0.4.0 (#982)
- Implement ooni resources downloader (#811)
- Improve the CMakeLists.txt file (#983)

# MeasurementKit 0.3.9 [2016-12-04]

- Revert "Add workaround for macOS"

# MeasurementKit 0.3.8 [2016-12-04]

- Make sure --disable-traceroute actually works
- Add workaround for macOS

# MeasurementKit 0.3.7 [2016-12-02]

- Allow to quickly disable traceroute

# MeasurementKit 0.3.6 [2016-12-01]

- http/request: don't redirect if `*max_request <= 0` (#908)
- Log dns debug to the correct logger (#912) (#914)
- web-connectivity: log errors (#916)
- bufferevent: use `BEV_OPT_DEFER_CALLBACKS` (#924)
- Fix several warnings (#926)
- `ooni_reporter.cpp`: make sure we submit report id (#927)

# MeasurementKit 0.3.5 [2016-11-01]

- a few `web_connectivity` fixes (#880, #889, #890)
- fix progress in emitted progress json (#886)

# MeasurementKit 0.3.4 [2016-10-28]

- switch test collector to b.collector.test.ooni.io (#880)
- remove `./build/android/library` (#870)
- fixing `web_connectivity` bug #867

# MeasurementKit 0.3.3 [2016-10-23]

- `connect.cpp`: increase default net/timeout (#872)
- `web_connectivity`: set the accessible key (#871)
- Make `no_collector`/`no_file_report` really usable (#859)

# MeasurementKit 0.3.2 [2016-10-03]

- `ooni_test`: continue even if we cannot submit an entry
- for testing use the discarding https collector deployed on heroku
- clanups and other small changes
- update android and ios to compile using latest dependencies

# MeasurementKit 0.3.1 [2016-10-03]

- update dependencies (yes, I was optimistic yesterday)

# MeasurementKit 0.3.0 [2016-10-02]

We are now entering in stable land. There are some outstanding issues
like making sure dependencies are up to date and that documentation is
in sync with code, but we can take care of those in subsequent patch
releases, if needed. We have been testing this version of MK for quite
a while now, and it really looks like good.

Compared to previous 0.3.0-beta.3, this release includes some goodies
from master that are very inlikely to impact on stability. Namely:

- flesh out basic contribution guide (#819)
- backport simple portability changes from #820 (#821)
- report: allow to pretty print entry (#825)
- very lite refactoring of runner (#826)

# MeasurementKit 0.3.0-beta.3 [2016-09-19]

- ooni: refactor geoip to cache openned databases (#809)
- reduce tarball size by not shipping geoip
- ooni: allow caller to set probe_{ip,asn,cc} (#816)
- ooni: fix regress by changing collector-url

# MeasurementKit 0.3.0-beta.2 [2016-09-15]

- ooni: allow to disable collector
- geoip: skip compiling binaries
- ooni: count entries and emit progress
- ooni: allow to optionally avoid writing reports to disk
- http: put geoip databases in current working dir
- *: make sure all errors are named Error

# MeasurementKit 0.3.0-beta.1 [2016-09-01]

- Improve .gitignore
- Merge stable branch into release/v0.3.0 branch
- Fix build with --disable-integration-tests

# MeasurementKit 0.3.0-beta [2016-08-31]

- autogen.sh: don't list embedded-mk as dependency (#796)
- teach acinclude.m4 to use brew's OpenSSL (#797)
- sketch out cmake build system (mainly for Windows) (#798)
- implement incremental ooni collector (#765)
- run OONI tests in parallel (#768)

# MeasurementKit 0.2.9 [2016-08-31]

- Make sure install.sh is included when we build release

# MeasurementKit 0.3.0-alpha.1 [2016-08-25]

- fix type of `getopt()` return value
- fix build for Android
- improve docs
- `net_test.hpp`: add `set_error_filepath()`
- change Android output archive name to be `measurement_kit-$version-android_jni${optional_build_version}.tag.bz2`

# MeasurementKit 0.3.0-alpha [2016-08-24]

- Add command line interface and also build binary executable
- Add OONI's web connectivity test
- Improve NDT test implementation: add support for waiting in queue, convert NDT into a real OONI test, fix way in which speed is measured
- `error.hpp`: allows to add an error a list of child errors
- add `fmap.hpp`: allows to map() over a vector
- `logger.hpp`: add EOF handler and allow to write logs on logfile, allow code to specify that the log message is in JSON format
- `net_test.hpp`: pass error to begin() and end(), add `on_entry` handler, add handlers for entering into `begin` and `end` states
- add `parallel.hpp`: allows to run functions in parallel and terminates only when all parallel functions have terminated (this interface is single threaded, not multi threaded, thus parallelism is only achieved when one function pauses waiting for I/O)
- add `range.hpp`: to generate numbers in a given range (such as in Python)
- `version.hpp`: add function to get library version
- `http.hpp`: implement following redirection and case-insensitive headers search
- `report/entry.hpp` now derives from nlohmann/json using public inheritance rather than private inheritance
- Update nlohmann/json.hpp to v2.0.2
- Update `tls_verify.c` to v1.15
- mlabns: allow to specify alternative mlabns base url
- net: add workarounds for when libevent's SSL bufferevents emit EOF before emitting data received before EOF, make emitter code more robust
- ooni: it is now possible to avoid saving autonomous system number and country code, add code to lookup the real IP address of the resolver, refactor code to use GeoIP APIs
- Update external dependencies versions
- Minor changes and bug fixes

# MeasurementKit 0.2.8 [2016-08-18]

- Updated dependencies
- Many improvements and changes in cross build scripts

# MeasurementKit 0.2.7 [2016-08-02]

- By default don't use OONI collector but the testing collector to avoid
  submitting integration tests results as OONI tests
- Update ChangeLog
- Bump patch version number

# MeasurementKit 0.2.6 [2016-07-31]

- Use OONI's default collector
- Update ChangeLog
- Bump patch version number

# MeasurementKit 0.2.5 [2016-07-13]

- Allow to `./configure --disable-integration-tests`
- Cherry pick 6d6f118e9 (fix TLS timeout bug)
- Bump patch version number

# MeasurementKit 0.2.4 [2016-07-10]

- Makefile.am: fix -release and -version-info flags
- bump path version number
- Add script to generate source package
- Use https collector by default
- Fix NDT example usage string

# MeasurementKit 0.2.3 [2016-07-08]

- make sure podspec uses up-to-date version number
- bump version number to v0.2.3

# MeasurementKit 0.2.2 [2016-07-08]

- document v0.2.1 release (I forgot to do that)
- properly bump version number (again, I forgot to do that)
- add script to automate release tasks
- and document v0.2.2 release

# MeasurementKit 0.2.1 [2016-07-08]

- use jessie64 rather than trusty64 in Vagrant file to make
  sure we work on debian stable
- make sure autogen.sh works ok on jessie64
- fix a bug that prevented headers to be installed when $DESTDIR
  wasn't specified

# MeasurementKit 0.2.0 [2016-06-30]

- autogen.sh: with -n do not use the network
- fix net/connect timeout
- update documentation for v0.2.0
- bump version to v0.2.0

# MeasurementKit 0.2.0-beta.2 [2016-06-19]

- http/request_serializer: allow custom path
- refactoring and small fixes
- common/net_test: removed misleading identifier() function
- common/utils: export time related utils functions
- ooni: merge DSL and Impl tests, use functions to implement tests (#677)
- ooni: avoid collisions in test file names
- common/net_test: file_path => filepath

# MeasurementKit 0.2.0-beta.1 [2016-06-08]

- `ip_lookup()`: allow custom settings, reactor, and logger (required
   by Android app)

# MeasurementKit 0.2.0-beta [2016-06-07]

- add initial NDT client implementation
- add more continuous integration providers using docker
- add support for setting default CA bundle path
- updated http-parser to v2.7.0
- updated Catch to v1.5.0
- add precompiled dependencies for Android and iOS
- upgrade Android build scripts to NDK r11c
- switch to use libevent's upstream repository instead of our fork
- peg GeoIP to v2.7.9 rather than using the master branch
- update libressl to v2.3.6
- add more documentation for common
- start updating existing docs
- migrate the tree to use templates to mock API calls
- rationalize HTTP and mlabns APIs
- rationalize OONI tests DSL API (this would probably break apps)
- add client for OONI report protocol
- make Delegate more convenient
- make Error way more robust and convenient, e.g. allow to chain errors
- use define to increase robustness of error definitions
- allow to pass flags to logger to convey extended semantic, e.g. state update
- add more helpful MOCK macros
- unify NetTest and NetTestDsl object models (OONI not yet ready for that)
- rename Poller as Reactor (more precise name); Poller is now a React implement.
- Reactor: add `loop_with_initial_event_and_connectivity`
- rename Async as Runner (more precise name)
- make Settings more useful
- add nlohmann/json as external header
- rewrite report::Entry using nlohmann/json via private inheritance
- FIX: make sure `readn()` never consumes too much stack
- export `report` headers as public API now that it uses `report::Entry`
- make sure we don't ignore possible errors when writing report
- remove unused, incomplete Tor controller
- downgrade minimum iOS platform from 9.0 to 7.1
- use `std::promise<>` and `std::future<>` for increased robustness
- Poller: make sure we ignore `SIGPIPE`
- significantly increase code coverage (now greater than 93%)
- make sure we handle `EPIPE`
- FIX: make sure OONI code produces spec compliant reports
- refactor OoniTestImpl replacing InputGenerator with much simpler code
- add to OONI support for geolookup and for automatically submitting reports

# MeasurementKit 0.2.0-alpha [2016-05-12]

We are not ready to declare a stable release yet, because tons of things still need love. However, we've reached a point where we could tag an alpha release. Too many changes, hence listing them in the order in which I see them when reading the huge diff since the previous stable release:

- autogenerate toplevel headers
- rewrite async
- add more functional programming abstractions
- allow to bind context to errors
- rename the Maybe object as ErrorOr
- remove evbuffer wrapper
- introduce lexical_cast
- use templates rather than Libs object to make code testable
- all global objects are now `Var<>` rather than raw pointers
- more granular logger levels
- make logger thread safe
- the Poller is now known as Reactor (but Poller is still an implementation of Reactor)
- removed code to manage global dns resolver, now each test sets its own resolver
- now Settings maps strings to most scalar types
- now it is possible to cast from `Var<BaseClass>` to `Var<DerivedClass>`
- rewritten dns code from scratch to increase memory safety
- rewritten http code from scratch to increase memory safety
- prefix settings with module name, to avoid conflicts
- implement client for mlabns
- remove TransportInterface, make Transport abstract and pass around `Var<Transport>`
- rewrite from scratch the connect flow to increase memory safety
- implement SSL transport
- verify SSL certificates
- allow to connect many socket at once
- migrated OONI code to use JSON rather than YAML (thus replacing yaml-cpp dependency with nlohmann/json)
- as a consequence of previous change, remove boost from dependencies
- implement GeoIP using the old rather than the new maxmind library (not all free database available for new library)
- removed most dependency from tree and rely now on the `./build/dependency` script
- add ./autogen.sh script to automatically generate parts of the tree that it would be otherwise tedious to maintain
- rewritten from scratch and significantly improved travis.yml
- added more example files
- moved the mobile subtree below build along with the new `./build/dependency` script
- added basic listener
- more cleanups and bug fixes

To speed up cross compiling, this release would also be the first release to contain bits of compiled code (e.g. libressl) that could be downloaded during the cross compilation process.

# MeasurementKit 0.1.2 [2016-02-04]
- cleanups and bug fixes

# MeasurementKit 0.1.1 [2016-01-13]
- allow to specify report file path for OONI tests
- add missing documentation 
- add Vagrantfile
- mv ooni::NetTest ooni::NetTest to avoid confusion with common::NetTest
- misc fixes

# MeasurementKit 0.1.0 [2015-12-16]
- allow to clear DNS servers on Android and iOS
- doc: add examples and tutorials
- a few more small fixes here and there

# MeasurementKit 0.1.0-beta.4 [2015-12-12]
- http: avoid throwing runtime-error
- poller: add functions to manipulate default's evdns-base
- updated changelog file

# MeasurementKit 0.1.0-beta.3 [2015-12-09]
- readd documentation of private classes
- add support for mkdocs
- bugfix: make the Connection class non-copyable and non-movable
- fixes to simplify using cross-compiled android libraries
- make OONI tests set_verbose() accept a boolean value (true by default)
- improve iOS build system

# MeasurementKit 0.1.0-beta.2 [2015-12-07]
- install missing traceroute header
- shrink android build in size and create tarballs
- rename and simplify namespaces
    - rename measurement_kit to mk
    - remove namespace common
- update dependencies to latest version
- simplify transport usage
    - rename Transport to TransportInterface
    - reintroduce Transport as a proxy for Var<TransportInterface>
    - teach connect() to return Maybe<Transport>
- other minor changes

# MeasurementKit 0.1.0-beta.1 [2015-12-02]
- implemented code coverage using clang
- misc build system improvements
- make sure that dependencies headers do not appear in measurement-kit public headers
- fix build process to avoid installing dependencies headers for android
- ooni.hpp: more abstract api for running ooni tests (this changed the api of the ooni sublibrary)
- net.hpp: rename Buffer::foreach() to Buffer::for_each()
- net.hpp: modify Buffer::readline() to return Maybestd::string
- net.hpp: modify signature of Transport::on_data()
- net.hpp: modify signature of net::connect()
- common.hpp: add Async::global()
- common.hpp: implement the Maybe template
- moved many headers from include to src to make sure they are not part of the public api
- fix http-parser to throw common::Error subclasses on error
- net/stream.cpp: route common::Error exceptions received when reading/writing
- improve regress tests
- add more documentation

# MeasurementKit 0.1.0-alpha.1 [2015-11-21]
* Project name changed to MeasurementKit
* Most code has been rewritten using C++11
* Cleanup the API in:
    * common
    * dns
    * http
    * net
    * ooni
    * report
    * traceroute
* Implemented OONI tests:
    * dns injection
    * http invalid request line
    * tcp connect
* Many more changes with respect to LibNeubot (compared to that
  project, MeasurementKit is basically another project)

# LibNeubot 3.0.0 [2014-05-04]
* Rewrite NeubotPollable now that I know that, in C++, a structure can
  inherit from a class. As a result, the FooState structure is now gone
  and the API now looks like v1.0 again. That is, again the poller is
  passed to the Pollable constructor, not to init().
* Related to the previous change: clarified that the Pollable main
  purpose is to allow experiments in which Neubot uses LibNeubot.
* Related to the previous change: crank major (we're now at API 3.0).
* Take advantage of the API 3.0 cranking and install the headers
  at a different location (<neubot.h> becomes <libneubot/neubot.h>).
* Add (but do not use yet) joyent/http-parser as submodule.
* Update the OpenBSD port and fix the code accordingly (mainly cases
  in which mixed libevent 1.4 and 2.0 headers were being used).
* Related to the previous change: update README to better clarify
  which are the dependencies.
* Deprecate gen_cxx and neubot.hh, now that it's clear that the code
  will be written in C++ to ease the interaction with SWIG.
* Move testing code in `test/`.
* Significant improvements in gen_python, which now enforces the
  type safety (i.e., you can only pass to Pollable_foo() an instance
  of the Python Pollable class), and in general produces much
  less bloated and more pythonic Python code.
* Related to the previous change: half of the unit test is now gone
  because it was not typesafe (we passed integers to functions in
  hope that they were pointer to the right C/C++ objects).
* More minor changes, fixes and tweaks.

# LibNeubot 2.0.0 [2014-04-11]
* Add Android.mk to compile a static library for Android
* Remove the unused LibNeubot.java/gen_java thing
* Reimplement NeubotPollable using C++ and write C wrappers to
  provide a similar API (however, the arguments of the constructor
  and of attach() were changed, hence the API bump)
* Move Java code that was autogenerated with SWIG into the
  neubot/neubot_android repository
* Make sure gen_cxx generates code that works on Android: correct
  the order of the generated classes, replace the nonworking cast with
 the invocation of the ->pointer() method
* Unify gen_py/gen_python and libneubot.py/libneubot1.py: now
  gen_python generates a libneubot.py file that contains the old
  stuff plus the stuff that was in libneubot1.py, moreover, the
  gen_py script and libneubot1.py were removed
* Regen libneubot_python
* Make sure shared C functions (e.g., log.h and utils.h) are
  correctly exported to C++
* While bumping the API, unbreak the resolve() API
* While touching the Pollable, reimplement timeouts using
  the support provided by libevent
* Realize that the destruction of objects must flow from the
  derived classes to the base classes (as C++ does) not the
  other way round (as PyNeubot does)
* Add some defines needed to compile on Android
* Export the logs to the logcat to ease the debugging

# LibNeubot 1.0.1 [2014-02-18]
* Tweak gen_cxx to generate code that SWIG can handle
* Use SWIG to generate Java and Python wrappers

# LibNeubot 1.0.0 [2013-12-15]
* Return status_t in NeubotPoller_defer_{read,write}
* Pass opaque, not pollable, to NeubotPollable callbacks
* libneubot.json: Add and use hooks, slots and __destructor__
* Add easier-to-use libneubot1.py wrappers
* Add neubot.hh, wrappers for C++

# LibNeubot 0.1.0 [2013-12-12]
* Initial release
