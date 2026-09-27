# UET Multi-Campus Network Project — Viva Questions & Answers

**Project:** Hierarchical Multi-Campus University Network (Cisco Packet Tracer)  
**Team:** Muhammad Hamza Shahid (SE-08), Muhammad Sohaib Aslam (SE-13), Mirza Zain Ali Baig (SE-20), Muhammad Muneeb Qureshi (SE-43)  
**Files:** `UET_CN_Lab_Report_.pdf` | `cn project.pkt`

> **How to use this file:** Read the question first, try to answer in your own words, then check the answer. Answers are written in simple English so you can explain them easily in viva.

---

## Table of Contents

1. [General Project Questions](#section-1-general-project-questions)
2. [Topology & Network Design](#section-2-topology--network-design)
3. [IP Addressing & VLSM](#section-3-ip-addressing--vlsm)
4. [VLANs](#section-4-vlans)
5. [Routers & Device Roles](#section-5-routers--device-roles)
6. [OSPF (Internal Routing)](#section-6-ospf-internal-routing)
7. [BGP (Border/ISP Routing)](#section-7-bgp-borderisp-routing)
8. [WAN Triangle & Redundancy](#section-8-wan-triangle--redundancy)
9. [Switches (Layer 2 & Layer 3)](#section-9-switches-layer-2--layer-3)
10. [DHCP](#section-10-dhcp)
11. [Servers (Web, Email, FTP)](#section-11-servers-web-email-ftp)
12. [ACLs & Security](#section-12-acls--security)
13. [Wireless](#section-13-wireless)
14. [Testing & Troubleshooting](#section-14-testing--troubleshooting)
15. [Basic Computer Network Concepts](#section-15-basic-computer-network-concepts)
16. [Packet Tracer & Simulation](#section-16-packet-tracer--simulation)
17. [Quick Revision Cheat Sheet](#section-17-quick-revision-cheat-sheet)

---

## Section 1: General Project Questions

### Q1. What is your project about?
**Answer:** We designed a complete computer network for UET Lahore with three campuses — Main Campus, Sub-Campus 1, and Sub-Campus 2. Each campus has three departments (Computer Science, Electrical Engineering, and Administration), plus wireless users and servers. We built everything in Cisco Packet Tracer using routers, switches, VLANs, OSPF, BGP, DHCP, and security rules (ACLs).

---

### Q2. Why did you choose a multi-campus design?
**Answer:** A real university has multiple buildings or campuses that are far apart. Each campus needs its own local network, but all campuses must still talk to each other and share central services like web, email, and FTP servers. A multi-campus design copies how real organizations connect their branches.

---

### Q3. How many campuses are in your project?
**Answer:** Three — Main Campus (hub), Sub-Campus 1, and Sub-Campus 2.

---

### Q4. How many departments does each campus have?
**Answer:** Three — Computer Science (CS), Electrical Engineering (EE), and Administration (Admin).

---

### Q5. Which tool did you use to simulate the network?
**Answer:** Cisco Packet Tracer. It lets us place routers, switches, PCs, and servers, configure them, and test connectivity with ping, traceroute, web browser, email, and FTP.

---

### Q6. What is the main goal of your network?
**Answer:** To connect all three campuses securely, allow departments to communicate, provide internet through an ISP, host central services (web, email, FTP), assign IPs automatically with DHCP, and block unauthorized access using ACLs.

---

### Q7. What routing protocols did you use and why?
**Answer:**  
- **OSPF** — inside each campus and between internal routers (fast, automatic route learning).  
- **BGP** — between border routers and the ISP (used on the internet and between different organizations).  
- **Static default route** — to send unknown traffic to the ISP.

---

### Q8. What private IP range does your whole network use?
**Answer:** `192.168.0.0/16` private block. Each campus gets its own `/24` subnet: Main = `192.168.1.0/24`, Sub-Campus 1 = `192.168.2.0/24`, Sub-Campus 2 = `192.168.3.0/24`.

---

### Q9. How many routers are in your network?
**Answer:** 8 routers total:
1. ISP-Router  
2. BR-Main (Border Router — Main)  
3. BR-SC1 (Border Router — Sub-Campus 1)  
4. BR-SC2 (Border Router — Sub-Campus 2)  
5. IR-Main (Internal Router — Main)  
6. IR-SC1 (Internal Router — Sub-Campus 1)  
7. IR-SC2 (Internal Router — Sub-Campus 2)  
8. IR-Server (Server Farm Router)

---

### Q10. How many switches are in your network?
**Answer:** 6 switches total — 3 Layer 3 switches (L3-Core-SW, L3-SW-SC1, L3-SW-SC2) and 3 Layer 2 access switches (SW-Main, SW-SC1, SW-SC2).

---

### Q11. What servers did you configure?
**Answer:** Three central servers at Main Campus:
- Web Server — `192.168.1.5` (HTTP port 80, HTTPS port 443)
- Email Server — `192.168.1.6` (SMTP port 25, POP3 port 110)
- FTP Server — `192.168.1.7` (FTP port 21)

---

### Q12. What security feature blocks Admin users from the web server?
**Answer:** Extended ACL (Access Control List) named `PROTECT_SERVER_FARM` and `BLOCK_ADMIN_WEB`. It denies TCP traffic on ports 80 and 443 from Admin subnets (`192.168.x.64/27`) to the web server `192.168.1.5`.

---

### Q13. What is the difference between a border router and an internal router in your project?
**Answer:**  
- **Border router** — sits at the edge; connects to ISP and other campuses using BGP; handles WAN links.  
- **Internal router** — sits inside the campus; connects L3 switch to border router; runs OSPF for local subnets.

---

### Q14. What does "hierarchical network design" mean in your project?
**Answer:** The network is organized in layers:
- **Access layer** — PCs, printers, APs connect to L2 switches  
- **Distribution/Core layer** — L3 switches do inter-VLAN routing  
- **WAN/Core edge** — Border routers connect campuses and ISP  

This makes the network easier to manage and scale.

---

### Q15. What is the OEL form in your report?
**Answer:** OEL (Outcomes Evaluation Lab) form is a checklist where we answered the teacher's requirements — number of campuses, devices, servers, routing protocols, IP addressing, security rules, etc. It proves our design meets the lab requirements.

---

## Section 2: Topology & Network Design

### Q16. Draw or explain your network topology in simple words.
**Answer:** Three campuses are connected in a triangle through border routers (BR-Main, BR-SC1, BR-SC2). Each campus has an internal router, an L3 switch, and access switches. All border routers also connect to one ISP router. Main Campus has a separate server farm router (IR-Server) for web, email, and FTP servers.

---

### Q17. What is the WAN triangle in your project?
**Answer:** A triangle-shaped connection between three border routers:
- BR-Main ↔ BR-SC1 (`10.0.0.0/30`)
- BR-Main ↔ BR-SC2 (`10.0.0.4/30`)
- BR-SC1 ↔ BR-SC2 (`10.0.0.8/30`)

If one link fails, traffic can still flow through the other two links.

---

### Q18. Why use a triangle instead of only one link between campuses?
**Answer:** For **redundancy** (backup paths). If the direct link between Main and Sub-Campus 1 fails, traffic can go through Sub-Campus 2 instead. This is called failover.

---

### Q19. Which router connects the university to the internet (ISP)?
**Answer:** BR-Main connects to the ISP-Router on link `203.0.113.0/30` (BR-Main = `203.0.113.1`, ISP = `203.0.113.2`). All campuses can reach the internet through BGP and OSPF paths.

---

### Q20. Do all three border routers connect to the ISP?
**Answer:** Yes. Each border router has its own `/30` link to the ISP-Router:
- BR-Main → `203.0.113.0/30`
- BR-SC1 → `203.0.113.4/30`
- BR-SC2 → `203.0.113.8/30`

---

### Q21. What is the role of IR-Server router?
**Answer:** It is a dedicated router for the server farm. It connects the web, email, and FTP servers to the rest of the network and applies ACLs to protect the servers. Its gateway IP on the server subnet is `192.168.1.1`.

---

### Q22. How does a PC in Sub-Campus 1 reach the web server at Main Campus?
**Answer:**  
1. PC sends packet to its default gateway (L3 switch SVI).  
2. L3 switch routes to IR-SC1 via OSPF.  
3. IR-SC1 sends to BR-SC1.  
4. BR-SC1 uses OSPF/BGP to reach Main Campus subnets.  
5. Packet arrives at IR-Server / L3-Core-SW and reaches `192.168.1.5`.

---

### Q23. What is a point-to-point (/30) link?
**Answer:** A `/30` subnet has only 2 usable IP addresses — one for each end of the link. Example: `10.0.0.0/30` has `.1` and `.2`. It is used between two routers directly connected by one cable.

---

### Q24. What are the internal router links in your project?
**Answer:** `/30` links between internal routers and L3 switches / border routers, for example:
- IR-Main ↔ L3-Core-SW: `10.1.0.0/30`
- IR-Main ↔ BR-Main: `10.1.0.4/30`
- IR-Server ↔ L3-Core-SW: `10.1.0.8/30`
- IR-SC1 ↔ L3-SW-SC1: `10.2.0.0/30`
- IR-SC2 ↔ L3-SW-SC2: `10.3.0.0/30`

---

### Q25. What is the difference between LAN and WAN in your project?
**Answer:**  
- **LAN** — inside each campus (192.168.x.x subnets, switches, PCs).  
- **WAN** — links between campuses and ISP (10.0.0.x and 203.0.113.x subnets, border routers).

---

### Q26. How many end devices are allowed per unit (campus)?
**Answer:** Per campus: 30 PCs, 4 wireless devices (2 tabs + 2 smartphones), 1 printer per department, and 30 cellular devices via wireless.

---

### Q27. What is the device inventory count from your OEL form?
**Answer:** 4 internal routers, 4 border routers (including ISP), 1 ISP router, 3 L3 core switches, and 6 L2 access switches.

---

### Q28. Why is Main Campus called the "hub"?
**Answer:** Because it hosts the central server farm (web, email, FTP) and is the main connection point. All sub-campuses depend on it for shared services.

---

### Q29. What happens if BR-Main goes down?
**Answer:** OSPF automatically finds another path. Traffic from Main Campus internal network may be affected, but Sub-Campus 1 and Sub-Campus 2 can still communicate through BR-SC1 ↔ BR-SC2 link. Your report shows only 1–2 packet loss during failover test.

---

### Q30. What is AS (Autonomous System) in your project?
**Answer:** AS is a group of networks under one administration with one routing policy. In your project:
- ISP and BR-Main = AS 65000
- BR-SC1 = AS 65001
- BR-SC2 = AS 65002

BGP is used between different AS numbers.

---

## Section 3: IP Addressing & VLSM

### Q31. What is VLSM?
**Answer:** VLSM (Variable Length Subnet Masking) means dividing a big network into smaller subnets of different sizes. We took each campus `/24` and split it into `/27` subnets — one per department.

---

### Q32. Why did you use /27 subnets for departments?
**Answer:** A `/27` subnet gives 30 usable host IPs (32 total minus network and broadcast). That is enough for about 30 PCs per department, which matches the lab requirement.

---

### Q33. How many usable hosts does a /27 subnet provide?
**Answer:** 30 usable hosts. Formula: 2^(32-27) - 2 = 32 - 2 = 30.

---

### Q34. What is the subnet mask of /27 in dotted decimal?
**Answer:** `255.255.255.224`

---

### Q35. What is the CS department subnet at Main Campus?
**Answer:** VLAN 10 — Network: `192.168.1.0/27`, Mask: `255.255.255.224`, Gateway: `192.168.1.1`, Host range: `.11` to `.20` (DHCP), Broadcast: `192.168.1.31`

---

### Q36. What is the EE department subnet at Main Campus?
**Answer:** VLAN 20 — Network: `192.168.1.32/27`, Gateway: `192.168.1.33`, Host range: `.41` to `.50`, Broadcast: `192.168.1.63`

---

### Q37. What is the Admin department subnet at Main Campus?
**Answer:** VLAN 30 — Network: `192.168.1.64/27`, Gateway: `192.168.1.65`, Host range: `.75` to `.84`, Broadcast: `192.168.1.95`

---

### Q38. What is the wireless subnet at Main Campus?
**Answer:** VLAN 40 — Network: `192.168.1.96/27`, Gateway: `192.168.1.97`, Host range: `.98` to `.126`, Broadcast: `192.168.1.127`

---

### Q39. Repeat the same for Sub-Campus 1 (192.168.2.0/24).
**Answer:**  
- CS (VLAN 10): `192.168.2.0/27`, GW `192.168.2.1`  
- EE (VLAN 20): `192.168.2.32/27`, GW `192.168.2.33`  
- Admin (VLAN 30): `192.168.2.64/27`, GW `192.168.2.65`  
- Wireless (VLAN 41): `192.168.2.96/27`, GW `192.168.2.97`

---

### Q40. Repeat the same for Sub-Campus 2 (192.168.3.0/24).
**Answer:**  
- CS (VLAN 10): `192.168.3.0/27`, GW `192.168.3.1`  
- EE (VLAN 20): `192.168.3.32/27`, GW `192.168.3.33`  
- Admin (VLAN 30): `192.168.3.64/27`, GW `192.168.3.65`  
- Wireless (VLAN 42): `192.168.3.96/27`, GW `192.168.3.97`

---

### Q41. What are the static IPs of your servers?
**Answer:**  
| Server | IP | Gateway | Services |
|--------|-----|---------|----------|
| Web_Server_Main | 192.168.1.5 | 192.168.1.1 | HTTP 80, HTTPS 443 |
| Email_Server_Main | 192.168.1.6 | 192.168.1.1 | SMTP 25, POP3 110 |
| FTP_Server_Main | 192.168.1.7 | 192.168.1.1 | FTP 21 |

---

### Q42. What is a default gateway?
**Answer:** The IP address of the router (or L3 switch SVI) that a PC sends packets to when the destination is on another network. Example: CS PC at Main uses `192.168.1.1` as default gateway.

---

### Q43. What is the difference between public and private IP in your project?
**Answer:**  
- **Private IPs** (192.168.x.x, 10.x.x.x) — used inside the university; not routable on the real internet.  
- **Public IPs** (203.0.113.x, 105.12.32.x) — used on WAN links to ISP; routable on internet.

---

### Q44. How many public IPs did the ISP allocate?
**Answer:** 10 public IPs in range `105.12.32.15` to `105.12.32.24/25`. Last two are for static server mapping; rest are for NAT Overload (PAT).

---

### Q45. What is NAT/PAT mentioned in your OEL form?
**Answer:** NAT (Network Address Translation) converts private IPs to public IPs for internet access. PAT (Port Address Translation) lets many private devices share one public IP using different port numbers. Like many people in a building sharing one street address but different apartment numbers.

---

### Q46. Why use 203.0.113.x for WAN links?
**Answer:** `203.0.113.0/24` is a documentation/test range (RFC 5737) commonly used in labs and Packet Tracer instead of real public IPs.

---

### Q47. What is network address vs broadcast address?
**Answer:**  
- **Network address** — first IP of subnet (identifies the subnet itself). Example: `192.168.1.0`  
- **Broadcast address** — last IP of subnet (sent to all hosts in subnet). Example: `192.168.1.31`  
Neither can be assigned to a PC.

---

### Q48. How did you avoid IP conflicts between campuses?
**Answer:** Each campus uses a different third octet: `.1` for Main, `.2` for SC1, `.3` for SC2. Same VLAN numbers (10, 20, 30) exist at each campus but with different IP subnets, so there is no conflict.

---

## Section 4: VLANs

### Q49. What is a VLAN?
**Answer:** VLAN (Virtual Local Area Network) is a logical group of devices that act like they are on the same switch, even if they are on different physical switches. It separates traffic — CS users cannot directly talk to EE users at Layer 2 without a router.

---

### Q50. Why did you use VLANs?
**Answer:** To separate departments for security and organization. CS, EE, Admin, Wireless, and Server Farm each get their own VLAN. Broadcast traffic stays inside each VLAN.

---

### Q51. List all VLANs in your project.
**Answer:**  
| VLAN ID | Name | Used At |
|---------|------|---------|
| 10 | CS_DEPT | All campuses |
| 20 | EE_DEPT | All campuses |
| 30 | ADMIN_DEPT | All campuses |
| 40 | WIRELESS_MAIN | Main Campus |
| 41 | WIRELESS_SC1 | Sub-Campus 1 |
| 42 | WIRELESS_SC2 | Sub-Campus 2 |
| 50 | SERVER_FARM | Main Campus |
| 99 | MGMT | All campuses (management) |

---

### Q52. Why do wireless VLANs differ per campus (40, 41, 42)?
**Answer:** Each campus has its own wireless subnet and access point. Different VLAN IDs help identify which campus the wireless traffic belongs to and keep IP addressing separate.

---

### Q53. What is inter-VLAN routing?
**Answer:** Routing between different VLANs. A Layer 3 device (router or L3 switch) is needed because VLANs are separate at Layer 2. Our L3 switches have SVI interfaces (one IP per VLAN) to route between them.

---

### Q54. What is an SVI?
**Answer:** SVI (Switched Virtual Interface) is a virtual interface on a Layer 3 switch for a VLAN. Example: `interface vlan 10` with IP `192.168.1.1` acts as the gateway for all CS PCs in VLAN 10.

---

### Q55. What is VLAN 99 used for?
**Answer:** Management VLAN. Used for managing switches and network devices separately from user traffic. Keeps management traffic secure and organized.

---

### Q56. Can two PCs in the same VLAN ping each other without a router?
**Answer:** Yes, if they are in the same subnet and same VLAN, they communicate at Layer 2 through the switch. No routing needed. This is what Test 1 (intra-department ping) verifies.

---

### Q57. Can a CS PC ping an EE PC without a router?
**Answer:** No. CS is VLAN 10 and EE is VLAN 20. They are different VLANs, so a Layer 3 device (L3 switch or router) must route between them. This is Test 2 (inter-VLAN ping).

---

### Q58. What is the native VLAN?
**Answer:** The VLAN on a trunk port that carries untagged traffic. By default it is VLAN 1 on Cisco devices. In exams, teachers may ask — know that untagged frames use native VLAN.

---

## Section 5: Routers & Device Roles

### Q59. What router model did you use?
**Answer:** Cisco 2911 routers for all 8 routers.

---

### Q60. What is the router-id of BR-Main?
**Answer:** `1.1.1.1` (configured under OSPF and BGP).

---

### Q61. List all router IDs in your project.
**Answer:**  
- BR-Main: 1.1.1.1  
- BR-SC1: 2.2.2.2  
- BR-SC2: 3.3.3.3  
- L3-Core-SW: 4.4.4.4  
- IR-Main: 5.5.5.5  
- IR-SC1: 6.6.6.6  
- IR-SC2: 7.7.7.7  
- IR-Server: 8.8.8.8  
- ISP-Router: 9.9.9.9

---

### Q62. What does `no shutdown` do on an interface?
**Answer:** It turns the interface **ON** (enables it). By default, Cisco interfaces may be administratively down. Without `no shutdown`, the link will not work.

---

### Q63. What is `write memory` or `copy running-config startup-config`?
**Answer:** Saves the current configuration to NVRAM so it survives a router reboot. Without saving, config is lost on restart.

---

### Q64. What is the purpose of ISP-Router?
**Answer:** It simulates the Internet Service Provider. It runs BGP AS 65000 and peers with all three campus border routers. It represents the internet cloud in Packet Tracer.

---

### Q65. Why do border routers run both OSPF and BGP?
**Answer:**  
- **OSPF** — learns routes inside the university network.  
- **BGP** — exchanges routes with ISP and other campuses (between different AS).  
Border router is the boundary between internal (OSPF) and external (BGP) routing.

---

### Q66. What does `default-information originate` do in OSPF?
**Answer:** It makes the router advertise a default route (`0.0.0.0/0`) to other OSPF routers. So all internal routers learn "send unknown traffic to the border router."

---

### Q67. What is the static default route on BR-Main?
**Answer:** `ip route 0.0.0.0 0.0.0.0 203.0.113.2` — sends all unknown traffic to the ISP-Router.

---

## Section 6: OSPF (Internal Routing)

### Q68. What is OSPF?
**Answer:** OSPF (Open Shortest Path First) is a link-state routing protocol. Routers share map of the network and calculate the shortest path. It is used inside our university network.

---

### Q69. Why use OSPF instead of only static routes?
**Answer:** With many subnets and redundant links, static routes are hard to manage. OSPF automatically updates routes when links go up or down (failover). Much easier for a large network.

---

### Q70. What OSPF areas did you use?
**Answer:**  
- **Area 0** (backbone) — Main Campus, WAN triangle links, ISP connections  
- **Area 1** — Sub-Campus 1 internal networks  
- **Area 2** — Sub-Campus 2 internal networks

---

### Q71. What is OSPF Area 0?
**Answer:** The backbone area. All other areas must connect to Area 0. In our project, WAN links and Main Campus are in Area 0. It is the central hub for OSPF.

---

### Q72. What does `network 10.1.0.0 0.0.0.3 area 0` mean?
**Answer:** It tells OSPF to enable OSPF on any interface whose IP matches `10.1.0.0` with wildcard mask `0.0.0.3` (which means only `10.1.0.0` and `10.1.0.1` — a /30). Those interfaces join Area 0.

---

### Q73. What is a wildcard mask?
**Answer:** Used in OSPF `network` commands (opposite of subnet mask). `0.0.0.3` means "care about all bits except last 2." For a /30 link, wildcard is `0.0.0.3`.

---

### Q74. How do you check OSPF neighbors?
**Answer:** `show ip ospf neighbor` — should show neighbors in **FULL** state. FULL means they successfully exchanged routing information.

---

### Q75. What does FULL state mean in OSPF?
**Answer:** Two routers have fully synchronized their link-state databases. Routing is working. If state is INIT or 2-WAY only, something may be wrong.

---

### Q76. How does OSPF help cross-campus communication (Test 3)?
**Answer:** When PC_CS_1 (Main) pings PC_CS_Sub1_1 (SC1), OSPF on all internal and border routers provides the path. `tracert` shows hops through IR-Main → BR-Main → BR-SC1 → IR-SC1 → L3-SW-SC1.

---

### Q77. What is the OSPF process ID in your project?
**Answer:** Process ID `1` on all routers (`router ospf 1`). Note: process ID is locally significant — does not need to match between routers.

---

### Q78. What is the difference between OSPF and RIP?
**Answer:**  
- OSPF — link-state, faster convergence, no hop limit, used in large networks.  
- RIP — distance-vector, max 15 hops, slower, older.  
We chose OSPF because our multi-campus network needs fast failover and scalability.

---

### Q79. What is route redistribution?
**Answer:** Sharing routes from one routing protocol into another. Border routers redistribute between OSPF (internal) and BGP (external). Example: OSPF learns 192.168.1.0/27, BGP advertises it to other AS.

---

### Q80. Which devices run OSPF in your network?
**Answer:** All 8 routers plus all 3 L3 switches (11 devices total).

---

## Section 7: BGP (Border/ISP Routing)

### Q81. What is BGP?
**Answer:** BGP (Border Gateway Protocol) is the routing protocol used on the internet between different organizations (Autonomous Systems). It decides which path to take between ISPs and large networks.

---

### Q82. Why use BGP in your project?
**Answer:** Because we have multiple Autonomous Systems (ISP AS 65000, SC1 AS 65001, SC2 AS 65002) that need to exchange routes. BGP is the standard for inter-AS routing.

---

### Q83. What are the AS numbers in your project?
**Answer:**  
- ISP-Router and BR-Main: AS **65000**  
- BR-SC1: AS **65001**  
- BR-SC2: AS **65002**

---

### Q84. What is a BGP neighbor?
**Answer:** Another router with which BGP exchanges routing tables. Example on BR-Main: neighbors are ISP (`203.0.113.2`), BR-SC1 (`10.0.0.2`), and BR-SC2 (`10.0.0.6`).

---

### Q85. How do you verify BGP is working?
**Answer:** `show ip bgp summary` — State should be **Established** and show number of prefixes received/sent.

---

### Q86. What does `network 192.168.1.0 mask 255.255.255.224` do in BGP?
**Answer:** Tells BGP to advertise the CS subnet (`192.168.1.0/27`) to BGP neighbors so other campuses and ISP know how to reach it.

---

### Q87. What is the difference between iBGP and eBGP?
**Answer:**  
- **eBGP** — BGP between different AS (e.g., BR-Main AS 65000 ↔ BR-SC1 AS 65001).  
- **iBGP** — BGP within same AS.  
Our project mainly uses eBGP between campuses and ISP.

---

### Q88. Why does ISP-Router peer with all three border routers?
**Answer:** So each campus has a direct path to the internet. If one campus link fails, it can still use WAN triangle to reach ISP through another border router.

---

### Q89. What is BGP router-id?
**Answer:** A unique 32-bit identifier for a BGP router (usually written as IP like 1.1.1.1). Used to identify the router in BGP updates. BR-Main uses 1.1.1.1.

---

### Q90. Can OSPF and BGP run on the same router?
**Answer:** Yes. Border routers run both. OSPF handles internal campus routes; BGP handles external routes to ISP and other campuses.

---

## Section 8: WAN Triangle & Redundancy

### Q91. What is network redundancy?
**Answer:** Having backup paths so if one link or device fails, traffic still flows through another path. Our WAN triangle provides this.

---

### Q92. Explain the three WAN links between border routers.
**Answer:**  
1. BR-Main (10.0.0.1) ↔ BR-SC1 (10.0.0.2) — `10.0.0.0/30`  
2. BR-Main (10.0.0.5) ↔ BR-SC2 (10.0.0.6) — `10.0.0.4/30`  
3. BR-SC1 (10.0.0.9) ↔ BR-SC2 (10.0.0.10) — `10.0.0.8/30`

---

### Q93. What did Test 7 (Redundancy Check) show?
**Answer:** Before shutting down a link on Main Border Router, traffic used one path. After shutdown, traffic automatically used a different path with only 1–2 packet loss. This proves OSPF failover works.

---

### Q94. What is failover?
**Answer:** Automatic switch to a backup path when the primary path fails. OSPF recalculates routes and sends traffic through the next best path.

---

### Q95. Why is redundancy important for a university network?
**Answer:** Students and staff need continuous access to email, web, and files. If one link breaks, classes and work should not stop. Redundancy keeps the network available.

---

## Section 9: Switches (Layer 2 & Layer 3)

### Q96. What is the difference between Layer 2 and Layer 3 switch?
**Answer:**  
- **Layer 2** — forwards frames using MAC addresses; handles VLANs; no IP routing.  
- **Layer 3** — can also route between VLANs using IP; has `ip routing` enabled.

---

### Q97. What switch models did you use?
**Answer:**  
- Layer 3: Cisco 3560 (L3-Core-SW, L3-SW-SC1, L3-SW-SC2)  
- Layer 2: Cisco 2960 (SW-Main, SW-SC1, SW-SC2)

---

### Q98. What does `ip routing` do on L3-Core-SW?
**Answer:** Enables the switch to act as a router and forward packets between VLANs using SVI interfaces.

---

### Q99. What is a trunk port?
**Answer:** A port that carries traffic for **multiple VLANs** between switches. Uses 802.1Q tagging to label which VLAN each frame belongs to.

---

### Q100. What is an access port?
**Answer:** A port assigned to **one VLAN only**. PCs and printers connect to access ports. Example: Fa0/1–10 on SW-SC1 are access ports in VLAN 10 (CS).

---

### Q101. What VLANs are allowed on the trunk between L3-Core-SW and SW-Main?
**Answer:** VLANs 10, 20, 30, 40, 50, and 99.

---

### Q102. What is `switchport mode trunk`?
**Answer:** Configures the port as a trunk port to carry multiple VLANs.

---

### Q103. What is `switchport access vlan 10`?
**Answer:** Puts that port in VLAN 10 as an access port. Devices on that port belong to CS department.

---

### Q104. What is `no switchport` on L3 switch?
**Answer:** Turns a physical port into a **routed port** (like a router interface) instead of a switchport. Used on links to IR-Main and IR-Server.

---

### Q105. How do you verify VLAN configuration?
**Answer:** `show vlan brief` — shows VLAN IDs, names, and which ports are assigned.

---

### Q106. How do you verify trunk links?
**Answer:** `show interfaces trunk` — shows trunk ports, encapsulation (802.1Q), and allowed VLANs.

---

## Section 10: DHCP

### Q107. What is DHCP?
**Answer:** DHCP (Dynamic Host Configuration Protocol) automatically gives IP address, subnet mask, default gateway, and DNS server to PCs. Users do not need to type IP settings manually.

---

### Q108. Where is DHCP configured in your project?
**Answer:** On each L3 switch — DHCP pools for each VLAN/department. Example: L3-SW-SC1 has pools CS_SC1, EE_SC1, ADMIN_SC1, WIRELESS_SC1.

---

### Q109. Why use `ip dhcp excluded-address`?
**Answer:** Reserves some IPs so DHCP does not assign them. Usually excludes gateway, servers, and network/broadcast addresses. Example: `excluded-address 192.168.2.1 192.168.2.10` keeps .1 (gateway) and .2–.10 free for static devices.

---

### Q110. What is the default gateway in DHCP pool CS_SC1?
**Answer:** `192.168.2.1` — the SVI of VLAN 10 on L3-SW-SC1.

---

### Q111. What DNS server is given by DHCP?
**Answer:** `192.168.1.6` — the Email Server IP (also acts as DNS in this lab since no separate DNS server is used).

---

### Q112. Does Main Campus use DHCP or static IPs?
**Answer:** Main Campus servers use **static IPs**. Sub-campuses use **DHCP** for PCs (as per OEL form). DHCP pools are on L3 switches.

---

### Q113. How do you check DHCP leases?
**Answer:** `show ip dhcp binding` on the L3 switch — shows which MAC address got which IP.

---

### Q114. What happens when a new PC joins the CS VLAN at Sub-Campus 1?
**Answer:**  
1. PC sends DHCP Discover broadcast.  
2. L3-SW-SC1 DHCP pool CS_SC1 responds with Offer.  
3. PC gets IP like 192.168.2.11, mask 255.255.255.224, gateway 192.168.2.1, DNS 192.168.1.6.

---

## Section 11: Servers (Web, Email, FTP)

### Q115. What is the IP of the web server?
**Answer:** `192.168.1.5` (Web_Server_Main). Also local web servers at sub-campuses: `192.168.2.5` and `192.168.3.5`.

---

### Q116. Which ports does the web server use?
**Answer:** Port **80** (HTTP) and Port **443** (HTTPS).

---

### Q117. What is HTTP vs HTTPS?
**Answer:**  
- **HTTP** — normal web traffic, not encrypted.  
- **HTTPS** — encrypted web traffic (secure).  
Our ACL blocks both ports 80 and 443 for Admin users.

---

### Q118. What is the email server IP and domain?
**Answer:** IP: `192.168.1.6`, Domain: `university.com`. Email addresses like `hamza@main.university.com`.

---

### Q119. What ports does email use?
**Answer:**  
- **SMTP (25)** — sending email  
- **POP3 (110)** — receiving email

---

### Q120. List email accounts on the server.
**Answer:**  
| Username | Password | Example Email |
|----------|----------|---------------|
| hamza | 123 | hamza@main.university.com |
| zain | 123 | (server account) |
| sohaib | 123 | sohaib@main.university.com |

PC_CS_1 uses hamza, PC_CS_Sub2_1 uses sohaib, PC_CS_Sub1_1 uses numan/arslan@main.university.com.

---

### Q121. Can Admin department access email even though web is blocked?
**Answer:** Yes. ACL only blocks ports 80 and 443 (web). SMTP (25) and POP3 (110) are still allowed. Admin can send and receive email.

---

### Q122. What is the FTP server IP?
**Answer:** `192.168.1.7`

---

### Q123. What FTP accounts did you create?
**Answer:**  
| Username | Password | Permissions |
|----------|----------|-------------|
| student | 123 | Read and List only |
| faculty | uet123 | Read, Write, Delete, Rename, List (full) |

---

### Q124. What is FTP used for?
**Answer:** File Transfer Protocol — uploading and downloading files to/from a server. Port 21. Students can only read; faculty have full access.

---

### Q125. How did you test web server access (Test 4)?
**Answer:** Opened web browser on PC_CS_1 (Main), PC_CS_Sub1_1 (SC1), and PC_CS_Sub2_1 (SC2) and accessed `http://192.168.1.5`. CS departments can access; Admin cannot.

---

## Section 12: ACLs & Security

### Q126. What is an ACL?
**Answer:** ACL (Access Control List) is a set of rules that permit or deny traffic. Like a security guard checking packets — "this traffic can pass, this traffic is blocked."

---

### Q127. What is the difference between standard and extended ACL?
**Answer:**  
- **Standard ACL** — filters only by source IP.  
- **Extended ACL** — filters by source IP, destination IP, protocol (TCP/UDP), and port number.  
We use **extended ACL** because we need to block specific ports (80, 443).

---

### Q128. Explain the PROTECT_SERVER_FARM ACL on IR-Server.
**Answer:** Applied inbound on the server farm interface. It **denies** TCP ports 80 and 443 from Admin subnets of all three campuses to web server 192.168.1.5:
- `192.168.1.64/27` (Main Admin)
- `192.168.2.64/27` (SC1 Admin)
- `192.168.3.64/27` (SC2 Admin)  
Last rule: `permit ip any any` (allow everything else).

---

### Q129. What does `deny tcp 192.168.2.64 0.0.0.31 host 192.168.1.5 eq 80` mean?
**Answer:** Block TCP traffic from Admin subnet SC1 (192.168.2.64–95) going to host 192.168.1.5 on port 80 (HTTP). The `0.0.0.31` is a wildcard mask for the source.

---

### Q130. What is an ACL wildcard mask?
**Answer:** `0` = must match, `1` = don't care. `0.0.0.31` means "match last 5 bits" which covers a /27 subnet (32 addresses).

---

### Q131. Why is the last ACL rule always `permit ip any any`?
**Answer:** ACLs have an **implicit deny all** at the end. If you don't add a permit rule, all traffic is blocked. `permit ip any any` allows everything that was not denied earlier.

---

### Q132. What is EXTERNAL_FIREWALL ACL on border routers?
**Answer:** Applied inbound on the ISP-facing interface. It:
- Permits established TCP connections (return traffic)  
- Permits ICMP (ping)  
- Denies direct inbound access to campus private networks from outside  
- Permits everything else

---

### Q133. Where is BLOCK_ADMIN_HTTP applied on L3-SW-SC1?
**Answer:** Inbound on `interface vlan 30` (Admin SVI). Blocks Admin users at SC1 from accessing web server on ports 80/443.

---

### Q134. What happens when Admin tries to open the web server?
**Answer:** Request times out or connection fails. ACL drops the packet. In simulation mode, you may see a red X at the switch/router boundary.

---

### Q135. How do you verify ACL is working?
**Answer:** `show access-lists` — shows hit counters (how many packets matched each rule). If deny rule counter increases when Admin tries web access, ACL is working.

---

### Q136. What is the difference between ACL applied `in` vs `out`?
**Answer:**  
- **in** — filters traffic **entering** the interface (coming in).  
- **out** — filters traffic **leaving** the interface (going out).  
Our ACLs are mostly applied **inbound**.

---

### Q137. Why block only Admin and not CS or EE?
**Answer:** Lab requirement (OEL form point 9): Admin department should not access the central HTTP web server. CS and EE need web access for academic work.

---

## Section 13: Wireless

### Q138. How is wireless implemented in your project?
**Answer:** Access Points (AP-Main, AP-SC1, AP-SC2) at each campus connect to the L3 switch. Wireless clients get IPs from DHCP in wireless VLAN (40, 41, or 42).

---

### Q139. What VLAN does wireless use at Main Campus?
**Answer:** VLAN 40 (WIRELESS_MAIN), subnet `192.168.1.96/27`, gateway `192.168.1.97`.

---

### Q140. Do wireless users have the same network access as wired PCs?
**Answer:** Yes, they are on their own subnet but can reach other campuses and servers through the same routing (OSPF/BGP) as wired users, unless blocked by ACL.

---

## Section 14: Testing & Troubleshooting

### Q141. What is ping used for?
**Answer:** Tests if two devices can reach each other at IP level. Command: `ping 192.168.1.5`. Success = "Reply from..."; failure = "Request timed out."

---

### Q142. What is tracert (traceroute)?
**Answer:** Shows every router (hop) between source and destination. Helps debug routing problems. Used in Test 3 to see cross-campus path.

---

### Q143. What does Test 1 verify?
**Answer:** Intra-department ping — two PCs in the **same VLAN** can communicate. Example: PC_CS_1 to PC_CS_2.

---

### Q144. What does Test 2 verify?
**Answer:** Inter-VLAN ping — PCs in **different VLANs** of same campus can communicate through L3 switch. Example: PC_CS_1 to PC_EE_1.

---

### Q145. What does Test 3 verify?
**Answer:** Cross-campus connectivity via OSPF. PC at Main Campus pings PC at Sub-Campus 1. Tracert shows the route through border routers.

---

### Q146. What does Test 5 verify?
**Answer:** FTP access. Login as `student` / `123`, run `dir` to list files on FTP server.

---

### Q147. List important troubleshooting commands.
**Answer:**  
| Command | Device | Purpose |
|---------|--------|---------|
| `show ip route` | Routers, L3 SW | View routing table |
| `show ip ospf neighbor` | Routers, L3 SW | Check OSPF neighbors |
| `show ip bgp summary` | Border routers | Check BGP sessions |
| `show vlan brief` | Switches | View VLANs |
| `show interfaces trunk` | L3 switches | View trunk ports |
| `show ip dhcp binding` | L3 switches | View DHCP leases |
| `show access-lists` | Routers, L3 SW | View ACL hits |
| `show running-config` | Any | Full configuration |
| `ping` | PC | Test connectivity |
| `tracert` | PC | Trace route path |

---

### Q148. What does `show ip route` display?
**Answer:** Routing table. Codes: **C** = connected, **O** = OSPF, **B** = BGP, **S** = static. Shows how router forwards packets.

---

### Q149. If ping fails, what steps do you check?
**Answer:**  
1. Is PC IP/gateway correct?  
2. Is interface `no shutdown`?  
3. Is VLAN/trunk correct on switch?  
4. Is route present in `show ip route`?  
5. Is OSPF neighbor FULL?  
6. Is ACL blocking traffic?  
7. Is cable connected in Packet Tracer?

---

### Q150. What is the simulation mode ACL proof?
**Answer:** In Packet Tracer simulation mode, when Admin tries to access web server, a red X appears at the device where ACL drops the packet. Visual proof that security rule works.

---

## Section 15: Basic Computer Network Concepts

### Q151. What are the 7 layers of OSI model? (Name at least 4)
**Answer:**  
1. Physical — cables, signals  
2. Data Link — MAC, switches, VLANs  
3. Network — IP, routers, routing  
4. Transport — TCP, UDP, ports  
5. Session — manages connections  
6. Presentation — encryption, formatting  
7. Application — HTTP, FTP, SMTP  

Our project mainly uses Layer 2 (VLANs), Layer 3 (IP routing), and Layer 4–7 (services).

---

### Q152. What is TCP vs UDP?
**Answer:**  
- **TCP** — reliable, checks delivery (used by HTTP, FTP, SMTP).  
- **UDP** — fast, no guarantee (used by DNS, video streaming).  
Our ACL rules specify **tcp** for web and email ports.

---

### Q153. What is a MAC address?
**Answer:** Physical address burned into a network card. Used at Layer 2 by switches. Example: `00:1A:2B:3C:4D:5E`. Different from IP address.

---

### Q154. What is the difference between IP address and MAC address?
**Answer:**  
- **IP** — logical address, can change, used for routing between networks.  
- **MAC** — physical address, fixed on NIC, used inside same LAN.

---

### Q155. What is DNS and did you use it?
**Answer:** DNS (Domain Name System) converts names like `google.com` to IP addresses. In our project, email clients point directly to IP `192.168.1.6` — no separate DNS server required for the lab.

---

### Q156. What is a firewall?
**Answer:** A security device/rule that blocks or allows traffic. Our EXTERNAL_FIREWALL ACL on border routers acts as a basic firewall against unauthorized inbound traffic.

---

### Q157. What is encapsulation?
**Answer:** Adding headers at each layer when data travels down the stack. Application data → TCP header → IP header → Ethernet frame. Routers remove/add headers at each hop.

---

### Q158. What is ARP?
**Answer:** ARP (Address Resolution Protocol) finds MAC address of a device when you know its IP. Needed before sending frames on local network. PC asks "who has 192.168.1.1?" and gateway replies with MAC.

---

### Q159. What is broadcast domain?
**Answer:** A set of devices that receive each other's broadcast frames. Each VLAN is a separate broadcast domain. Routers separate broadcast domains.

---

### Q160. What is collision domain?
**Answer:** Devices whose frames can collide on shared media. Switches separate collision domains (each port is its own). Hubs share one collision domain.

---

## Section 16: Packet Tracer & Simulation

### Q161. What is Cisco Packet Tracer?
**Answer:** A network simulation tool by Cisco. You can drag routers, switches, PCs, configure them with CLI, and test without real hardware.

---

### Q162. What file format saves your Packet Tracer project?
**Answer:** `.pkt` file — our project is saved as `cn project.pkt`.

---

### Q163. What is the difference between Realtime and Simulation mode?
**Answer:**  
- **Realtime** — works like normal network, fast.  
- **Simulation** — slows down packets so you can see them travel hop by hop. Good for demos and ACL proof.

---

### Q164. How do you open CLI on a router in Packet Tracer?
**Answer:** Click the device → **CLI** tab → press Enter. You get `Router>` prompt. Type `enable` for privileged mode, `configure terminal` for config mode.

---

### Q165. What are the Cisco IOS modes?
**Answer:**  
- `Router>` — User EXEC mode (limited commands)  
- `Router#` — Privileged EXEC (`enable`) — show commands  
- `Router(config)#` — Global config (`configure terminal`)  
- `Router(config-if)#` — Interface config  
- `Router(config-router)#` — Routing protocol config

---

### Q166. What does a green triangle on a link mean in Packet Tracer?
**Answer:** The link is up and interfaces are active (no shutdown, cables connected).

---

### Q167. What does a red triangle on a link mean?
**Answer:** Link is down — cable missing, interface shutdown, or misconfiguration.

---

## Section 17: Quick Revision Cheat Sheet

### Key IPs to Remember
| Device/Subnet | IP |
|---------------|-----|
| Web Server | 192.168.1.5 |
| Email Server | 192.168.1.6 |
| FTP Server | 192.168.1.7 |
| Main CS Gateway | 192.168.1.1 |
| SC1 CS Gateway | 192.168.2.1 |
| SC2 CS Gateway | 192.168.3.1 |
| BR-Main (to ISP) | 203.0.113.1 |
| ISP-Router | 203.0.113.2 |

### Key Port Numbers
| Service | Port | Protocol |
|---------|------|----------|
| HTTP | 80 | TCP |
| HTTPS | 443 | TCP |
| FTP | 21 | TCP |
| SMTP (send email) | 25 | TCP |
| POP3 (receive email) | 110 | TCP |

### Key Protocols
| Protocol | Used For |
|----------|----------|
| OSPF | Internal routing (inside university) |
| BGP | External routing (ISP + between campuses) |
| DHCP | Automatic IP assignment |
| ACL | Security — permit/deny traffic |
| 802.1Q | VLAN tagging on trunk ports |

### Device Count
| Device | Count |
|--------|-------|
| Routers | 8 |
| L3 Switches | 3 |
| L2 Switches | 3 |
| Campuses | 3 |
| Departments per campus | 3 |
| Central Servers | 3 |

### One-Line Answers for Rapid Fire
- **VLAN?** → Logical LAN separation on a switch  
- **OSPF?** → Internal dynamic routing protocol  
- **BGP?** → External routing between AS  
- **ACL?** → Traffic filter rules  
- **SVI?** → VLAN gateway on L3 switch  
- **Trunk?** → Port carrying multiple VLANs  
- **/27?** → Subnet with 30 usable hosts  
- **/30?** → Point-to-point link (2 hosts)  
- **Default gateway?** → Router IP to reach other networks  
- **Redundancy?** → Backup path when link fails  

---

## Tips for Viva Day

1. **Start with the big picture** — "We built a 3-campus university network with 8 routers, VLANs, OSPF, BGP, and ACL security."

2. **Use simple examples** — Compare VLANs to separate floors in a building; gateway to the main door to other buildings.

3. **Know your IPs** — Web server (192.168.1.5), email (192.168.1.6), FTP (192.168.1.7).

4. **Explain WHY, not just WHAT** — Don't just say "we used OSPF." Say "we used OSPF because it automatically finds backup paths when a link fails."

5. **Mention your tests** — Ping same VLAN, ping different VLAN, ping different campus, web access, FTP, ACL block, redundancy test.

6. **If you don't know** — Say "That part was configured by my teammate" or "I would check with `show ip route`" instead of guessing.

---

*Total Questions: 167*  
*Generated from: UET_CN_Lab_Report_.pdf and cn project.pkt project documentation*
