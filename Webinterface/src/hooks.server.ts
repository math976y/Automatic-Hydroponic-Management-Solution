import type { Handle } from '@sveltejs/kit';
import { fetchRequestHandler } from '@trpc/server/adapters/fetch';
import { appRouter } from '$lib/trpc/router';

const endpoint = '/api/trpc';
export const handle: Handle = async ({ event, resolve }) => {
	if (event.url.pathname.startsWith(endpoint)) {
		return fetchRequestHandler({
			endpoint,
			req: event.request,
			router: appRouter,
			createContext() {
				return {};
			}
		});
	}

	const response = await resolve(event);
	return response;
};