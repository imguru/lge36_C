struct ip6_hdr {
  union {
    struct ip6_hdrctl {
      uint32_t ip6_un1_flow;   /* 24 bits of flow-ID */
      uint16_t ip6_un1_plen;   /* payload length */
      uint8_t  ip6_un1_nxt;    /* next header */
      uint8_t  ip6_un1_hlim;   /* hop limit */
    } ip6_un1;
    uint8_t ip6_un2_vfc;       /* 4 bits version, 4 bits priority */
  } ip6_ctlun;
  struct in6_addr ip6_src;      /* source address */
  struct in6_addr ip6_dst;      /* destination address */
};

#define ip6_vfc   ip6_ctlun.ip6_un2_vfc
#define ip6_flow  ip6_ctlun.ip6_un1.ip6_un1_flow
#define ip6_plen  ip6_ctlun.ip6_un1.ip6_un1_plen
#define ip6_nxt   ip6_ctlun.ip6_un1.ip6_un1_nxt
#define ip6_hlim  ip6_ctlun.ip6_un1.ip6_un1_hlim
#define ip6_hops  ip6_ctlun.ip6_un1.ip6_un1_hlim

/* Hop-by-Hop options header */
/* XXX should we pad it to force alignment on an 8-byte boundary? */
struct ip6_hbh {
  uint8_t  ip6h_nxt;        /* next header */
  uint8_t  ip6h_len;        /* length in units of 8 octets */
    /* followed by options */
};

/* Destination options header */
/* XXX should we pad it to force alignment on an 8-byte boundary? */
struct ip6_dest {
  uint8_t  ip6d_nxt;        /* next header */
  uint8_t  ip6d_len;        /* length in units of 8 octets */
    /* followed by options */
};

/* Routing header */
struct ip6_rthdr {
  uint8_t  ip6r_nxt;        /* next header */
  uint8_t  ip6r_len;        /* length in units of 8 octets */
  uint8_t  ip6r_type;       /* routing type */
  uint8_t  ip6r_segleft;    /* segments left */
    /* followed by routing type specific data */
};

/* Type 0 Routing header */
struct ip6_rthdr0 {
  uint8_t  ip6r0_nxt;       /* next header */
  uint8_t  ip6r0_len;       /* length in units of 8 octets */
  uint8_t  ip6r0_type;      /* always zero */
  uint8_t  ip6r0_segleft;   /* segments left */
  uint8_t  ip6r0_reserved;  /* reserved field */
  uint8_t  ip6r0_slmap[3];  /* strict/loose bit map */
  struct in6_addr  ip6r0_addr[1];  /* up to 23 addresses */
};

/* Fragment header */
struct ip6_frag {
  uint8_t   ip6f_nxt;       /* next header */
  uint8_t   ip6f_reserved;  /* reserved field */
  uint16_t  ip6f_offlg;     /* offset, reserved, and flag */
  uint32_t  ip6f_ident;     /* identification */
};

#define IP6F_OFF_MASK       0xfff8  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0006  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FRAG      0x0001  /* more-fragments flag */
