#include	"unpxti.h"

/*
 * Functions that convert XTI option values into printable strings.
 *
 * Note: XTI_DEBUG is defined as returning an array of t_uscalar_t's.
 * Our function xti_str_uscalard() checks that there is at least one entry
 * in the array and prints just the first entry.
 * Ditto for IP_OPTIONS, which is defined as returning an array of u_char's
 * and our function xti_str_uchard().
 */

static char	strres[128];	/* assume one opt at a time, so static is OK */

char *
xti_str_lend(struct t_opthdr *topt)		/* value length, decimal */
{
	snprintf(strres, sizeof(strres), "%lu (length of value)",
								topt->len - sizeof(struct t_opthdr));
	return(strres);
}

char *
xti_str_uscalard(struct t_opthdr *topt)	/* t_uscalar_t, decimal */
{
	if (topt->len < sizeof(struct t_opthdr) + sizeof(t_uscalar_t))
		return(xti_str_lend(topt));
	snprintf(strres, sizeof(strres), "%ld", *((t_uscalar_t *) (topt+1)));
	return(strres);
}

char *
xti_str_uchard(struct t_opthdr *topt)	/* unsigned char, decimal */
{
	if (topt->len < sizeof(struct t_opthdr) + sizeof(u_char))
		return(xti_str_lend(topt));
	snprintf(strres, sizeof(strres), "%d", *((u_char *) (topt+1)));
	return(strres);
}

char *
xti_str_ucharx(struct t_opthdr *topt)	/* unsigned char, hex */
{
	if (topt->len < sizeof(struct t_opthdr) + sizeof(u_char))
		return(xti_str_lend(topt));
	snprintf(strres, sizeof(strres), "0x%02x", *((u_char *) (topt+1)));
	return(strres);
}

char *
xti_str_yn(t_uscalar_t val)	/* internal function for yes/no values */
{
	if (val == T_YES)
		return("T_YES");
	else if (val == T_NO)
		return("T_NO");
	else {
		snprintf(strres, sizeof(strres), "(unknown value: %lu)", val);
		return(strres);
	}
}

char *
xti_str_syng(t_scalar_t val)		/* t_scalar_t, yes/no/gabage */
{
	if (val == T_YES)
		return("T_YES");
	else if (val == (T_YES|T_GARBAGE))
		return("T_YES|T_GARBAGE");
	else if (val == T_NO)
		return("T_NO");
	else {
		snprintf(strres, sizeof(strres), "(unknown value: %ld)", val);
		return(strres);
	}
}

char *
xti_str_uiyn(struct t_opthdr *topt)	/* unsigned int, yes/no */
{
	if (topt->len < sizeof(struct t_opthdr) + sizeof(u_int))
		return(xti_str_lend(topt));
	return(xti_str_yn((t_uscalar_t) *((u_int *) (topt+1))));
}

char *
xti_str_usyn(struct t_opthdr *topt)	/* t_uscalar_t, yes/no */
{
	if (topt->len < sizeof(struct t_opthdr) + sizeof(t_uscalar_t))
		return(xti_str_lend(topt));
	return(xti_str_yn(*((t_uscalar_t *) (topt+1))));
}

char *
xti_str_linger(struct t_opthdr *topt)	/* t_linger structure */
{
	struct t_linger	*tl;

	if (topt->len < sizeof(struct t_opthdr) + sizeof(struct t_linger))
		return(xti_str_lend(topt));
	tl = (struct t_linger *) (topt+1);
	if (tl->l_linger == T_UNSPEC)
		snprintf(strres, sizeof(strres), "%s, T_UNSPEC",
						xti_str_yn((t_uscalar_t) tl->l_onoff));
	else if (tl->l_linger == T_INFINITE)
		snprintf(strres, sizeof(strres), "%s, T_INFINITE",
						xti_str_yn((t_uscalar_t) tl->l_onoff));
	else
		snprintf(strres, sizeof(strres), "%s, %ld sec",
						xti_str_yn((t_scalar_t) tl->l_onoff), tl->l_linger);
	return(strres);
}

char *
xti_str_kpalive(struct t_opthdr *topt)	/* t_kpalive structure */
{
	struct t_kpalive	*tk;

	if (topt->len < sizeof(struct t_opthdr) + sizeof(struct t_kpalive))
		return(xti_str_lend(topt));
	tk = (struct t_kpalive *) (topt+1);
	if (tk->kp_timeout == T_UNSPEC)
		snprintf(strres, sizeof(strres), "%s, T_UNSPEC",
				xti_str_syng((t_scalar_t) tk->kp_onoff));
	else
		snprintf(strres, sizeof(strres), "%s, %ld sec",
				xti_str_syng((t_scalar_t) tk->kp_onoff), tk->kp_timeout);
	return(strres);
}

char *
xti_str_flags(t_scalar_t flags)			/* t_optmgmt{}.flags */
{
	if      (flags == T_SUCCESS)	return("T_SUCCESS");
	else if (flags == T_FAILURE)	return("T_FAILURE");
	else if (flags == T_NOTSUPPORT)	return("T_NOTSUPPORT");
	else if (flags == T_READONLY)	return("T_READONLY");
	snprintf(strres, sizeof(strres), "(unknown flags value: %ld)", flags);
	return(strres);
}
