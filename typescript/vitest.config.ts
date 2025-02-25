import { defineConfig } from "vitest/config";

export default defineConfig({
    test: {
        reporters: ["verbose"],
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
