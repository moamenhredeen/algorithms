import { defineConfig } from "vitest/config";

export default defineConfig({
    test: {
        reporters: ['dot'],
        chaiConfig: {
            showDiff: false,
            truncateThreshold: 1000,
            includeStack: true,
        },
        onConsoleLog() {
            return false;
        },
        onStackTrace() {
            return false;
        },
    },
});
