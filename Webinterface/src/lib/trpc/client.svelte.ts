import { createTRPCClient, httpBatchLink, httpSubscriptionLink, loggerLink, splitLink } from '@trpc/client';
import { browser } from '$app/environment';
import { page } from '$app/state';
import type { AppRouter } from './router';

export function useTRPC() {
	return createTRPCClient<AppRouter>({
		  links: [
			// adds pretty logs to your console in development and logs errors in production
			loggerLink(),
			splitLink({
			// uses the httpSubscriptionLink for subscriptions
			condition: (op) => op.type === 'subscription',
			true: httpSubscriptionLink({
				url: `/api/trpc`,
			}),
			false: httpBatchLink({
				url: `/api/trpc`,
			}),
			}),
		],
	});
}